#ifndef _VIRTROOTFS_VR_OPS_H
#define _VIRTROOTFS_VR_OPS_H

#include "vr_fuse.h"

int vr_open (const char * path, struct fuse_file_info * info);

#endif
