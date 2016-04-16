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
#include <stddef.h>
#include <unistd.h>
#include <bstrlib.h>
#include <fuse.h>

void *vrfs_init(struct fuse_conn_info *conn) {
    const struct fuse_context *context = fuse_get_context();
    struct vrfs_data *data  = context->private_data;
    if(!data->index_path) {
        data->index_path = "/var/lib/auch/index";
    }
    if(!data->pool_path) {
        data->pool_path = "/var/lib/auch/packages";
    }
    return data;
}
