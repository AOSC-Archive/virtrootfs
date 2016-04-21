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
#include <errno.h>
#include <stddef.h>
#include <bstrlib.h>
#include <stdlib.h>
#include <fuse.h>

int vrfs_getattr(const char *path, struct stat *stbuf) {
	const struct fuse_context *context = fuse_get_context();
	
	char *phy_path = vrfs_resolve(path, context->pid);
    if (stat(phy_path, stbuf)==0) {
    	bcstrfree(phy_path);
        return 0;
    }
    bcstrfree(phy_path);
    return 1;
}
