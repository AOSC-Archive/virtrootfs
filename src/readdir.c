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
    int rc = 0;
    
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    
    /* Something goes here go get physical components of this dir */
    // phy_components = xxx;
	char *phy_components = "/ /bin/true"; // Testing usage
    
    char *u_pc, fname;
    struct stat oinfo, finfo;
    struct dirent *ptr;
	u_pc = "/"; // Testing usage
//	u_pc = strtok(phy_components, " ");  
//	while(u_pc != NULL){		
		stat(u_pc,&oinfo);
		if(S_ISDIR(oinfo.st_mode)) {
			dir = opendir(u_pc);
			while((ptr = readdir(dir)) != NULL) {
				chdir(u_pc);
				lstat(ptr->d_name,&finfo);
				// finfo passing is not working yet
				filler(buf, ptr->d_name, &finfo, 0);
			}
			closedir(dir);
		} else {
		// Files part has some issue.. though
			filler(buf, u_pc, NULL, 0);
		}
		
//		u_pc = strtok(NULL, " ");
//	}
    
    return rc;
}
