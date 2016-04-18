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

#pragma once

#define FUSE_USE_VERSION 26
#include <fuse.h>
#include <bstrlib.h>

struct vrfs_data {
    const char *index_path;
    const char *pool_path;
};

void *vrfs_init(struct fuse_conn_info *conn);
int vrfs_getattr(const char *path, struct stat *stbuf);
int vrfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t off, struct fuse_file_info *fi);
int vrfs_resolve(const bstring *virt_path, bstring *real_path, pid_t pid);
int vrfs_open(const char *path, struct fuse_file_info *fi);
int vrfs_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fi);
int vrfs_flush(const char *path, struct fuse_file_info *fi);

void vrfs_assert_failed(const char *expr, const char *file, unsigned int line);
#ifndef vrfs_assert
#define vrfs_assert(expr) ((expr) ? (void) 0 : vrfs_assert_failed(#expr, __FILE__, __LINE__))
#endif
