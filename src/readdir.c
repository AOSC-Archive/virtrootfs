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
#include <string.h>
#include <fuse.h>

int vrfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t off, struct fuse_file_info *fi) {
    const struct fuse_context *context = fuse_get_context();
    const struct vrfs_data *data  = context->private_data;
    DIR *dir;
    int rc = 0;
    
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    
    /* Something goes here go get physical components of this dir */
    // char **phy_components;
    // virt_to_phylist(path, phy_components);
    char *u1 = "/bin/true";
    char *u2 = "/etc/fstab";
	char *phy_components[] = {u1,u2}; // Testing usage
	int phy_comp_count = 2;
    
    struct stat finfo;
    
    char *u_pc;
	for (int i = 0; i<phy_comp_count; i++) {
		u_pc = phy_components[i];
		stat(u_pc, &finfo);
		
		printf("Phy count :%d\n", phy_comp_count);
		printf("Phy :%s\n", u_pc);
		
		filler(buf, strrchr(u_pc, '/')+sizeof(char), &finfo, 0);
	}
    
    return rc;
}
