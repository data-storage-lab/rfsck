/*
 * Copyright (c) 2003-2005 Silicon Graphics, Inc.
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it would be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write the Free Software Foundation,
 * Inc.,  51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <sys/uio.h>
#include "command.h"
#include "input.h"
#include "init.h"
#include "io.h"

static cmdinfo_t pwrite_cmd;

static void
pwrite_help(void)
{
	printf(_(
"\n"
" writes a range of bytes (in block size increments) from the given offset\n"
"\n"
" Example:\n"
" 'pwrite 512 20' - writes 20 bytes at 512 bytes into the open file\n"
"\n"
" Writes into a segment of the currently open file, using either a buffer\n"
" filled with a set pattern (0xcdcdcdcd) or data read from an input file.\n"
" The writes are performed in sequential blocks starting at offset, with the\n"
" blocksize tunable using the -b option (default blocksize is 4096 bytes),\n"
" unless a different write pattern is requested.\n"
" -S   -- use an alternate seed number for filling the write buffer\n"
" -i   -- input file, source of data to write (used when writing forward)\n"
" -d   -- open the input file for direct IO\n"
" -s   -- skip a number of bytes at the start of the input file\n"
" -w   -- call fdatasync(2) at the end (included in timing results)\n"
" -W   -- call fsync(2) at the end (included in timing results)\n"
" -B   -- write backwards through the range from offset (backwards N bytes)\n"
" -F   -- write forwards through the range of bytes from offset (default)\n"
" -R   -- write at random offsets in the specified range of bytes\n"
" -Z N -- zeed the random number generator (used when writing randomly)\n"
"         (heh, zorry, the -s/-S arguments were already in use in pwrite)\n"
#ifdef HAVE_PWRITEV
" -V N -- use vectored IO with N iovecs of blocksize each (pwritev)\n"
#endif
"\n"));
}

#ifdef HAVE_PWRITEV
static int
do_pwritev(
	int		fd,
	off64_t		offset,
	ssize_t		count,
	ssize_t		buffer_size)
{
	int vecs = 0;
	ssize_t oldlen = 0;
	ssize_t bytes = 0;

	/* trim the iovec if necessary */
	if (count < buffersize) {
		size_t	len = 0;
		while (len + iov[vecs].iov_len < count) {
			len += iov[vecs].iov_len;
			vecs++;
		}
		oldlen = iov[vecs].iov_len;
		iov[vecs].iov_len = count - len;
		vecs++;
	} else {
		vecs = vectors;
	}
	bytes = pwritev(fd, iov, vectors, offset);

	/* restore trimmed iov */
	if (oldlen)
		iov[vecs - 1].iov_len = oldlen;

	return bytes;
}
#else
#define do_pwritev(fd, offset, count, buffer_size) (0)
#endif

static int
do_pwrite(
	int		fd,
	off64_t		offset,
	ssize_t		count,
	ssize_t		buffer_size)
{
	if (!vectors)
		return pwrite(fd, buffer, min(count, buffer_size), offset);

	return do_pwritev(fd, offset, count, buffer_size);
}

static int
write_random(
	off64_t		offset,
	long long	count,
	unsigned int	seed,
	long long	*total)
{
	off64_t		off, range;
	ssize_t		bytes;
	int		ops = 0;

	srandom(seed);
	if ((bytes = (offset % buffersize)))
		offset -= bytes;
	offset = max(0, offset);
	if ((bytes = (count % buffersize)))
		count += bytes;
	count = max(buffersize, count);
	range = count - buffersize;

	*total = 0;
	while (count > 0) {
		if (range)
			off = ((offset + (random() % range)) / buffersize) *
				buffersize;
		else
			off = offset;
		bytes = do_pwrite(file->fd, off, buffersize, buffersize);
		if (bytes == 0)
			break;
		if (bytes < 0) {
			perror("pwrite");
			return -1;
		}
		ops++;
		*total += bytes;
		if (bytes < buffersize)
			break;
		count -= bytes;
	}
	return ops;
}

static int
write_backward(
	off64_t		offset,
	long long	*count,
	long long	*total)
{
	off64_t		end, off = offset;
	ssize_t		bytes = 0, bytes_requested;
	long long	cnt = *count;
	int		ops = 0;

	if ((end = off - cnt) < 0) {
		cnt += end;	/* subtraction, end is negative */
		end = 0;
	}
	*total = 0;
	*count = cnt;

	/* Do initial unaligned write if needed */
	if ((bytes_requested = (off % buffersize))) {
		bytes_requested = min(cnt, bytes_requested);
		off -= bytes_requested;
		bytes = do_pwrite(file->fd, off, bytes_requested, buffersize);
		if (bytes == 0)
			return ops;
		if (bytes < 0) {
			perror("pwrite");
			return -1;
		}
		ops++;
		*total += bytes;
		if (bytes < bytes_requested)
			return ops;
		cnt -= bytes;
	}

	/* Iterate backward through the rest of the range */
	while (cnt > end) {
		bytes_requested = min(cnt, buffersize);
		off -= bytes_requested;
		bytes = do_pwrite(file->fd, off, cnt, buffersize);
		if (bytes == 0)
			break;
		if (bytes < 0) {
			perror("pwrite");
			return -1;
		}
		ops++;
		*total += bytes;
		if (bytes < bytes_requested)
			break;
		cnt -= bytes;
	}
	return ops;
}

static int
write_buffer(
	off64_t		offset,
	long long	count,
	size_t		bs,
	int		fd,
	off64_t		skip,
	long long	*total)
{
	ssize_t		bytes;
	long long	bar = min(bs, count);
	int		ops = 0;

	*total = 0;
	while (count >= 0) {
		if (fd > 0) {	/* input file given, read buffer first */
			if (read_buffer(fd, skip + *total, bs, &bar, 0, 1) < 0)
				break;
		}
		bytes = do_pwrite(file->fd, offset, count, bar);
		if (bytes == 0)
			break;
		if (bytes < 0) {
			perror("pwrite");
			return -1;
		}
		ops++;
		*total += bytes;
		if (bytes <  min(count, bar))
			break;
		offset += bytes;
		count -= bytes;
		if (count == 0)
			break;
	}
	return ops;
}

static int
pwrite_f(
	int		argc,
	char		**argv)
{
	size_t		bsize;
	off64_t		offset, skip = 0;
	long long	count, total, tmp;
	unsigned int	zeed = 0, seed = 0xcdcdcdcd;
	size_t		fsblocksize, fssectsize;
	struct timeval	t1, t2;
	char		*sp, *infile = NULL;
	int		Cflag, qflag, uflag, dflag, wflag, Wflag;
	int		direction = IO_FORWARD;
	int		c, fd = -1;

	Cflag = qflag = uflag = dflag = wflag = Wflag = 0;
	init_cvtnum(&fsblocksize, &fssectsize);
	bsize = fsblocksize;

	while ((c = getopt(argc, argv, "b:BCdf:Fi:qRs:S:uV:wWZ:")) != EOF) {
		switch (c) {
		case 'b':
			tmp = cvtnum(fsblocksize, fssectsize, optarg);
			if (tmp < 0) {
				printf(_("non-numeric bsize -- %s\n"), optarg);
				return 0;
			}
			bsize = tmp;
			break;
		case 'C':
			Cflag = 1;
			break;
		case 'F':
			direction = IO_FORWARD;
			break;
		case 'B':
			direction = IO_BACKWARD;
			break;
		case 'R':
			direction = IO_RANDOM;
			break;
		case 'd':
			dflag = 1;
			break;
		case 'f':
		case 'i':
			infile = optarg;
			break;
		case 's':
			skip = cvtnum(fsblocksize, fssectsize, optarg);
			if (skip < 0) {
				printf(_("non-numeric skip -- %s\n"), optarg);
				return 0;
			}
			break;
		case 'S':
			seed = strtoul(optarg, &sp, 0);
			if (!sp || sp == optarg) {
				printf(_("non-numeric seed -- %s\n"), optarg);
				return 0;
			}
			break;
		case 'q':
			qflag = 1;
			break;
		case 'u':
			uflag = 1;
			break;
		case 'V':
			vectors = strtoul(optarg, &sp, 0);
			if (!sp || sp == optarg) {
				printf(_("non-numeric vector count == %s\n"),
					optarg);
				return 0;
			}
			break;
		case 'w':
			wflag = 1;
			break;
		case 'W':
			Wflag = 1;
			break;
		case 'Z':
			zeed = strtoul(optarg, &sp, 0);
			if (!sp || sp == optarg) {
				printf(_("non-numeric seed -- %s\n"), optarg);
				return 0;
			}
			break;
		default:
			return command_usage(&pwrite_cmd);
		}
	}
	if (((skip || dflag) && !infile) || (optind != argc - 2))
		return command_usage(&pwrite_cmd);
	if (infile && direction != IO_FORWARD)
		return command_usage(&pwrite_cmd);
	offset = cvtnum(fsblocksize, fssectsize, argv[optind]);
	if (offset < 0) {
		printf(_("non-numeric offset argument -- %s\n"), argv[optind]);
		return 0;
	}
	optind++;
	count = cvtnum(fsblocksize, fssectsize, argv[optind]);
	if (count < 0) {
		printf(_("non-numeric length argument -- %s\n"), argv[optind]);
		return 0;
	}

	if (alloc_buffer(bsize, uflag, seed) < 0)
		return 0;

	c = IO_READONLY | (dflag ? IO_DIRECT : 0);
	if (infile && ((fd = openfile(infile, NULL, c, 0)) < 0))
		return 0;

	gettimeofday(&t1, NULL);
	switch (direction) {
	case IO_RANDOM:
		if (!zeed)	/* srandom seed */
			zeed = time(NULL);
		c = write_random(offset, count, zeed, &total);
		break;
	case IO_FORWARD:
		c = write_buffer(offset, count, bsize, fd, skip, &total);
		break;
	case IO_BACKWARD:
		c = write_backward(offset, &count, &total);
		break;
	default:
		total = 0;
		ASSERT(0);
	}
	if (c < 0)
		goto done;
	if (Wflag)
		fsync(file->fd);
	if (wflag)
		fdatasync(file->fd);
	if (qflag)
		goto done;
	gettimeofday(&t2, NULL);
	t2 = tsub(t2, t1);

	report_io_times("wrote", &t2, (long long)offset, count, total, c,
			Cflag);
done:
	if (infile)
		close(fd);
	return 0;
}

void
pwrite_init(void)
{
	pwrite_cmd.name = "pwrite";
	pwrite_cmd.altname = "w";
	pwrite_cmd.cfunc = pwrite_f;
	pwrite_cmd.argmin = 2;
	pwrite_cmd.argmax = -1;
	pwrite_cmd.flags = CMD_NOMAP_OK | CMD_FOREIGN_OK;
	pwrite_cmd.args =
_("[-i infile [-d] [-s skip]] [-b bs] [-S seed] [-wW] [-FBR [-Z N]] [-V N] off len");
	pwrite_cmd.oneline =
		_("writes a number of bytes at a specified offset");
	pwrite_cmd.help = pwrite_help;

	add_command(&pwrite_cmd);
}
