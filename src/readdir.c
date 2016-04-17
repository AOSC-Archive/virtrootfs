/*
    Anthon Uniform Configuration Helper
    Copyright (C) 2016 StarBrilliant <m13253@hotmail.com>
    Copyright (C) 2016 Icenowy

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
#include <unistd.h>
#include <bstrlib.h>
#include <fuse.h>

int vrfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t off, struct fuse_file_info *fi) {
    const struct fuse_context *context = fuse_get_context();
    const struct vrfs_data *data  = context->private_data;
    DIR *dir;
    int err = 0;
    {
        bstring index_path = bfromcstr(data->index_path);
        vrfs_assert(index_path != NULL);
        if(path[0] != '/') {
            vrfs_assert(bcatblk(index_path, "/", 1) != BSTR_ERR);
        }
        vrfs_assert(bcatcstr(index_path, path) != BSTR_ERR);
        {
            char *c_index_path = bstr2cstr(index_path, ' ');
            vrfs_assert(index_path != NULL);
            dir = opendir(c_index_path);
            if(!dir) {
                err = errno;
            }
            bcstrfree(c_index_path);
        }
        bdestroy(index_path);
    }
    if(!dir) {
        return -err;
    }
    for(;;) {
        const struct dirent *dir_entry = readdir(dir);
        if(!dir_entry) {
            break;
        }
        filler(buf, dir_entry->d_name, NULL, 0);
    }
    if(dir) {
        closedir(dir);
    }
    return 0;
}
