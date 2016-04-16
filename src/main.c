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
#include <stddef.h>
#include <string.h>
#include <fuse.h>

#define VRFS_OPT(t, p, v) { t, offsetof(struct vrfs_data, p), v }

static const struct fuse_opt vrfs_opts[] = {
    VRFS_OPT("index=%s", index_path, 0),
    VRFS_OPT("pool=%s", pool_path, 0),
    FUSE_OPT_END
};

static const struct fuse_operations vrfs_ops = {
    .getattr    = vrfs_getattr,
    .readdir    = vrfs_readdir,
};

int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    struct vrfs_data data = {};
    fuse_opt_parse(&args, &data, vrfs_opts, NULL);
    return fuse_main(argc, argv, &vrfs_ops, &data);
}
