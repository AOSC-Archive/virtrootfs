/*
    Anthon Uniform Configuration Helper
    Copyright (C) 2016 StarBrilliant <m13253@hotmail.com>
    Copyright (C) 2016 Icenowy
    Copyright (C) 2016 bobcao3 <bobcaocheng@163.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "virtrootfs.h"
#include <dirent.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <bstrlib.h>
#include <fuse.h>

int vrfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t off, struct fuse_file_info *fi) {
	const struct fuse_context *context = fuse_get_context();
	const struct vrfs_data *data  = context->private_data;
	DIR *dir;

	char *phy_components[1024];
	int phy_comp_count = vrfs_resolve_dir(path, phy_components, context->pid, data->pool_path);

	struct stat finfo;

	char *u_pc;
	for (int i = 0; i<phy_comp_count; i++) {
		u_pc = phy_components[i];
		stat(u_pc, &finfo);

		bstring u_pc_b = bfromcstr(u_pc);
		bstring file = bmidstr(u_pc_b, strlen(path)+1, u_pc_b->slen-strlen(path)-1);
		filler(buf, (const char*) file->data, &finfo, 0);
		bdestroy(file);
		bdestroy(u_pc_b);

		bcstrfree(u_pc);
	}

	return 0;
}
