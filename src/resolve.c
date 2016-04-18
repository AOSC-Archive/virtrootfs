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
#include <bstrlib.h>
#include <unistd.h>

char* virt_to_phy(const char* virt) {
	return "/etc/fstab";	
}

int virt_to_phylist(const char* virt, char** phy_components) {
	char *u1 = "/bin/true";
    char *u2 = "/etc/fstab";
  //  phy_components = malloc(512);
    phy_components[0] = u1;
    phy_components[1] = u2;
	return 2;
}

int vrfs_resolve(const bstring *virt_path, bstring *real_path, pid_t pid) {
    // STUB
    /*
    index_file = index+virt_path
    if index_file does not exist
        return false
    elif index_file is directory
        real_path = index_file
        return true
    else
        env_file = "/proc/"+pid+"/environ"["AUCH_ENV"]
        imported_packages[] = open(env_file).readlines
        (provider_packages, exporter_packages)[] = open(index_file).readlines.split
        if any of imported_packages in provider_packages
            if the exporter_package is empty
                real_path = pool_path+provider_package+virt_path
            else
                real_path = pool_path+exporter_package+virt_path
            return true
        else
            return false
    */
    return 0;
}
