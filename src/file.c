/*
    Anthon Uniform Configuration Helper
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
#include <string.h>
#include <fuse.h>

int vrfs_open(const char *path, struct fuse_file_info *fi) {
	const struct fuse_context *context = fuse_get_context();
	const struct vrfs_data *data  = context->private_data;

	char *p = vrfs_resolve(path, context->pid, data->pool_path);
	if (p!=NULL) {
		printf("File open DBG: phy - %s\n", p);

		int fd = open(p, fi->flags);
		bcstrfree(p);
		if (fd == -1) return -errno;
	
		fi->fh = (unsigned long)fd;
	
		return 0;
	} else {
		bcstrfree(p);
		printf("File open DBG: phy can't be found\n", p);
		return 1;
	}
}

int vrfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi) {
	int i = pread(fi->fh, buf, size, offset);

	if (i == -1) return -errno;

	return i;
}

int vrfs_flush(const char *path, struct fuse_file_info *fi) {
	int fd = dup(fi->fh);
	if (fd == -1) {
		if (fsync(fi->fh) == -1) return -EIO;
		return -errno;
	}
	int res = close(fd);
	if (res == -1) return -errno;

	return 0;
}

