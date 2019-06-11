/*
 * Copyright (c) 2005 Silicon Graphics, Inc.
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

#include "command.h"
#include "input.h"
#include "init.h"
#include "quota.h"

static cmdinfo_t path_cmd;
static cmdinfo_t print_cmd;

static void
printpath(
	struct fs_path	*path,
	int		index,
	int		number,
	int		braces)
{
	fs_quota_stat_t	qstat;
	fs_project_t	*prj;
	int		c;

	if (index == 0) {
		printf(_("%s%sFilesystem          Pathname\n"),
		       number ? _("      ") : "",
		       foreign_allowed ? _("    ") : "");
	}
	if (number)
		printf(_("%c%03d%c "), braces? '[':' ', index, braces? ']':' ');
	if (foreign_allowed)
		printf("%s", (path->fs_flags & FS_FOREIGN) ? "(F) " : "    ");
	printf(_("%-19s %s"), path->fs_dir, path->fs_name);
	if (path->fs_flags & FS_PROJECT_PATH) {
		prj = getprprid(path->fs_prid);
		printf(_(" (project %u"), path->fs_prid);
		if (prj)
			printf(_(", %s"), prj->pr_name);
		printf(")");
	} else if (xfsquotactl(XFS_GETQSTAT, path->fs_name, 0, 0,
			       (void *)&qstat) == 0 && qstat.qs_flags) {
		c = 0;
		printf(" (");
		if (qstat.qs_flags & XFS_QUOTA_UDQ_ENFD)
			c = printf("uquota");
		else if (qstat.qs_flags & XFS_QUOTA_UDQ_ACCT)
			c = printf("uqnoenforce");
		if (qstat.qs_flags & XFS_QUOTA_GDQ_ENFD)
			c = printf("%sgquota", c ? ", " : "");
		else if (qstat.qs_flags & XFS_QUOTA_GDQ_ACCT)
			c = printf("%sgqnoenforce", c ? ", " : "");
		if (qstat.qs_flags & XFS_QUOTA_PDQ_ENFD)
			printf("%spquota", c ? ", " : "");
		else if (qstat.qs_flags & XFS_QUOTA_PDQ_ACCT)
			printf("%spqnoenforce", c ? ", " : "");
		printf(")");
	}
	printf("\n");
}

static int
pathlist_f(void)
{
	int		i;
	struct fs_path	*path;

	for (i = 0; i < fs_count; i++) {
		path = &fs_table[i];
		/* Table is ordered xfs first, then foreign */
		if (path->fs_flags & FS_FOREIGN && !foreign_allowed)
			break;
		printpath(path, i, 1, path == fs_path);
	}
	return 0;
}

static int
print_f(
	int		argc,
	char		**argv)
{
	int		i;
	struct fs_path	*path;

	for (i = 0; i < fs_count; i++) {
		path = &fs_table[i];
		if (path->fs_flags & FS_FOREIGN && !foreign_allowed)
			break;
		printpath(path, i, 0, 0);
	}
	return 0;
}

static int
path_f(
	int		argc,
	char		**argv)
{
	int	i;
	int	max = foreign_allowed ? fs_count : xfs_fs_count;

	if (fs_count == 0) {
		printf(_("No paths are available\n"));
		return 0;
	}

	if (argc <= 1)
		return pathlist_f();

	i = atoi(argv[1]);
	if (i < 0 || i >= max) {
		printf(_("value %d is out of range (0-%d)\n"),
			i, max - 1);
	} else {
		fs_path = &fs_table[i];
		pathlist_f();
	}
	return 0;
}

void
path_init(void)
{
	path_cmd.name = "path";
	path_cmd.altname = "paths";
	path_cmd.args = _("[N]");
	path_cmd.cfunc = path_f;
	path_cmd.argmin = 0;
	path_cmd.argmax = 1;
	path_cmd.flags = CMD_FLAG_ONESHOT | CMD_FLAG_FOREIGN_OK;
	path_cmd.oneline = _("set current path, or show the list of paths");

	print_cmd.name = "print";
	print_cmd.altname = "p";
	print_cmd.cfunc = print_f;
	print_cmd.argmin = 0;
	print_cmd.argmax = 0;
	print_cmd.flags = CMD_FLAG_ONESHOT | CMD_FLAG_FOREIGN_OK;
	print_cmd.oneline = _("list known mount points and projects");

	if (expert)
		add_command(&path_cmd);
	add_command(&print_cmd);
}
