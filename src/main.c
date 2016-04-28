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
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fuse.h>

#define VRFS_OPT(t, p, v) { t, offsetof(struct vrfs_data, p), v }

enum {
    VRFS_KEY_HELP,
    VRFS_KEY_VERSION,
};

static const struct fuse_opt vrfs_opts[] = {
    VRFS_OPT("index=%s",        index_path, 0),
    VRFS_OPT("pool=%s",         pool_path, 0),
    FUSE_OPT_KEY("--help",      VRFS_KEY_HELP),
    FUSE_OPT_KEY("--version",   VRFS_KEY_VERSION),
    FUSE_OPT_KEY("-f",          FUSE_OPT_KEY_KEEP),
    FUSE_OPT_KEY("-d",          FUSE_OPT_KEY_KEEP),
    FUSE_OPT_END
};

static const struct fuse_operations vrfs_ops = {
    .init       = vrfs_init,
    .getattr    = vrfs_getattr,
    .readdir    = vrfs_readdir,
    .open		= vrfs_open,
    .read		= vrfs_read,
    .flush		= vrfs_flush,
    .release	= vrfs_release,
};

static int vrfs_opt_proc(void *data, const char *arg, int key, struct fuse_args *outargs) {
    switch(key) {
    case VRFS_KEY_HELP:
        puts("Usage: virtrootfs [-fd] [-o index=INDEX,pool=POOL]");
        exit(0);
        return 0;
    case VRFS_KEY_VERSION:
        puts("Virtrootfs version unknown-git");
        exit(0);
        return 0;
    default:
        return 1;
    }
}

int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    struct vrfs_data data = {};
    if (fuse_opt_parse(&args, &data, vrfs_opts, vrfs_opt_proc) == -1) return 1;
    return fuse_main(args.argc, args.argv, &vrfs_ops, &data);
}
