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
#include <stdio.h>
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

int vrfs_resolve(const char *virt_path, char *real_path, pid_t pid) {
	// Fixme: Need to change this pool path to a dynamical one
    char* index = "/var/lib/auch/index";
    char* index_file;
    sprintf(index_file, "%s/%s", index, virt_path);
    struct stat finfo;
    if (!stat(index_file, &finfo)) {
        return 1;
    } else if (S_ISDIR(finfo.st_mode)) {
        real_path = index_file;
        return 0;
    } else {
        char *env_file;
        int pid = 0;
        sprintf(env_file, "/proc/%d/environ", pid);
        FILE *envf = fopen(env_file, "r");
        char *index_lines[256];
        char *line;
        int i = 0;
        fscanf(envf, "%s", line);
        while (line) {
        	index_lines[i] = line;
        	i++;
        	fscanf(envf, "%s", line);
        }
        for (int j = 0; j++; j<i) {
        	char *imported_f = index_lines[j];
        	char *line;
        	int i = 0;
        	FILE *imported = fopen(imported_f, "r");
        	fscanf(imported, "%s", line);
        	while (line) {
        		if (strcmp(line, virt_path)==0) {
        // Fixme: Need to change this pool path to a dynamical one
        			char* pool = "/var/lib/auch/packages";
        			sprintf(real_path, "%s/%s/%s", pool, imported, virt_path);
        		}
        		i++;
        		fscanf(imported, "%s", line);
        	}
        }
        /*
        (provider_packages, exporter_packages)[] = open(index_file).readlines.split
        if any of imported_packages in provider_packages
            if the exporter_package is empty
                real_path = pool_path+provider_package+virt_path
            else
               、 real_path = pool_path+exporter_package+virt_path
            return true
        else
            return false*/
    }
    return 1;
}
