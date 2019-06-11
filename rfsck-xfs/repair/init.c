/*
 * Copyright (c) 2000-2002,2005 Silicon Graphics, Inc.
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

#include "libxfs.h"
#include "globals.h"
#include "agheader.h"
#include "protos.h"
#include "err_protos.h"
#include "pthread.h"
#include "avl.h"
#include "bmap.h"
#include "incore.h"
#include "prefetch.h"
#include <sys/resource.h>

static void
ts_create(void)
{
	pthread_key_create(&dblkmap_key, NULL);
	pthread_key_create(&ablkmap_key, NULL);
}

static void
increase_rlimit(void)
{
	struct rlimit rl;

	/* Increase limits */
	if (getrlimit(RLIMIT_FSIZE, &rl) == -1) {
		perror("getrlimit");
		fprintf(stderr, _("getrlimit(RLIMIT_FSIZE) failed!\n"));
		exit(1);
	}
	if (rl.rlim_cur != RLIM_INFINITY) {
		rl.rlim_max = rl.rlim_cur = RLIM_INFINITY;
		if (setrlimit(RLIMIT_FSIZE, &rl) == -1) {
			perror("setrlimit");
			fprintf(stderr,
				_("setrlimit failed - current: %lld, max: %lld\n"),
				(unsigned long long)rl.rlim_cur,
				(unsigned long long)rl.rlim_max);
			exit(1);
		}
	}
}

void
xfs_init(libxfs_init_t *args)
{
	memset(args, 0, sizeof(libxfs_init_t));

	if (isa_file)  {
		args->disfile = 1;
		args->dname = fs_name;
		args->volname = NULL;
	} else  {
		args->disfile = 0;
		args->volname = fs_name;
		args->dname = NULL;
	}

	if (log_spec)  {	/* External log specified */
		args->logname = log_name;
		args->lisfile = (isa_file?1:0);
		/* XXX assume data file also means log file */
		/* REVISIT: Need to do fs sanity / log validity checking */
	}

	if (rt_spec)  {	/* RT device specified */
		args->rtname = rt_name;
		args->risfile = (isa_file?1:0);
		/* XXX assume data file also means rt file */
	}

	args->usebuflock = do_prefetch;
	args->setblksize = 0;
	args->isdirect = LIBXFS_DIRECT;
	if (no_modify)
		args->isreadonly = (LIBXFS_ISREADONLY | LIBXFS_ISINACTIVE);
	else if (dangerously)
		args->isreadonly = (LIBXFS_ISINACTIVE | LIBXFS_DANGEROUSLY);
	else
		args->isreadonly = LIBXFS_EXCLUSIVELY;

	if (!libxfs_init(args)) {
		/* would -d be an option? */
		if (!no_modify && !dangerously) {
			args->isreadonly = (LIBXFS_ISINACTIVE |
					    LIBXFS_DANGEROUSLY);
			if (libxfs_init(args))
				fprintf(stderr,
_("Unmount or use the dangerous (-d) option to repair a read-only mounted filesystem\n"));
		}
		do_error(_("couldn't initialize XFS library\n"));
	}

	ts_create();
	increase_rlimit();
	pftrace_init();
}
