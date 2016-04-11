/*
    Anthon Uniform Configuration Helper
    Copyright (C) 2016 StarBrilliant <m13253@hotmail.com
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
#include "vrfs_ops.h"

static const struct fuse_lowlevel_ops vrfs_ops = {
    .opendir    = vrfs_opendir,
};

int main(int argc, char *argv[]) {
    struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
    struct fuse_chan *chan;
    char *mountpoint;
    int err = -1;
    
    if(fuse_parse_cmdline(&args, &mountpoint, NULL, NULL) != -1) {
        chan = fuse_mount(mountpoint, &args);
        if(chan) {
            struct fuse_session *session;
            session = fuse_lowlevel_new(&args, &vrfs_ops, sizeof vrfs_ops, NULL);
            if(session) {
                if(fuse_set_signal_handlers(session) != -1) {
                    fuse_session_add_chan(session, chan);
                    err = fuse_session_loop(session);
                    fuse_remove_signal_handlers(session);
                    fuse_session_remove_chan(chan);
                }
                fuse_session_destroy(session);
            }
            fuse_unmount(mountpoint, chan);
        }
    }
    fuse_opt_free_args(&args);

    return err ? 1 : 0;
}
