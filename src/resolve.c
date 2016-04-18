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

int vrfs_resolve_dir(const char *virt_path, char** phy_components, pid_t pid) {
	return 0;
}

int vrfs_resolve(const char *virt_path, char *real_path, pid_t pid) {
// Get env_file name
	char *env_file;
   	sprintf(env_file, "/proc/%d/environ", pid);
	FILE *envf = fopen(env_file, "r");
	char *line;
	fscanf(envf, "%s", line);
// Get AUCH_ENV from env file
	int i = 0;
	char *index_lines[256];
	char* token;
	token = strtok(line, "^@");
	char *auch_env;
	while(token != NULL) {
		if (strlen(token)>=strlen("AUCH_ENV=")) {
			char* p;
			if (p=strstr(token, "AUCH_ENV=")) {
				auch_env = token + sizeof("AUCH_ENV=");
				break;
			}
		}
		i++;
		token = strtok(NULL, "^@");
	}
	char* endp = token = strtok(NULL, "^@");
	endp = (char) 0; // Cut the string
// Read the index file (AUCH_ENV) and try to match files
	FILE *index = fopen(auch_env, "r");
	char* imported_package;
	fscanf(index, "%s", imported_package);
	while (line) {
		char *pool = "/var/lib/auch/packages";
		char* phy_file_trial;
		sprintf(phy_file_trial, "%s/%s/%s", pool, imported, virt_path);
		if (access(phy_file_trial, 0)) {
			real_path = phy_file_trial;
			return 0;
		}
		fscanf(index, "%s", line);
	}
    return 1;
}
