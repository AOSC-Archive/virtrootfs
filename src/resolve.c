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
#include <bstrlib.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

bstring vrfs_resolve_index(pid_t pid) {
// Get env file
	bstring env = bformat("/proc/%d/environ", pid);
	FILE *fp;
	char* env_c = bstr2cstr(env, '\0');
	bstring env_cxt;
	bdestroy(env);
	if (NULL != (fp = fopen (env_c, "r"))) {
		env_cxt = bread ((bNread) fread, fp);
		fclose (fp);
	} else {
		bcstrfree(env_c);
		return NULL;
	}
	bcstrfree(env_c);
// Get AUCH_ENV
	struct bstrList *envs;
	bstring env_buf;
	if (NULL != (envs = bsplit (env_cxt, '\0'))) {
		bdestroy(env_cxt);
		bstring b_prefix = bfromcstr("AUCH_ENV=");
		for (int i=0; i < envs->qty - 1; i++) {
			bstring env_row = envs->entry[i];
			if ((bstrncmp(env_row, b_prefix, 3)==0)) {
				env_buf = bmidstr (env_row, blength(b_prefix), blength(env_row) - blength(b_prefix));
				bstrListDestroy (envs);
			bdestroy(b_prefix);
				return env_buf;
			}
		}
		bstrListDestroy (envs);
		bdestroy(b_prefix);
		return NULL;
	} else {
		bstrListDestroy (envs);
		bdestroy(env_cxt);
		return NULL;
	}
}

int vrfs_resolve_dir(const char *virt_path, char** phy_components, pid_t pid) {
	bstring env = vrfs_resolve_index(pid);
	if (env!=NULL) {
		char* env_c = bstr2cstr(env, '\0');
		printf("resolve dir env - DBG: %s\n",env_c);
		bcstrfree(env_c);
	} else {
		printf("resolve dir env - DBG: no AUCH_ENV found\n");
		bdestroy(env);
		return 0;
	}
// Read the index file (AUCH_ENV) and try to match files
	FILE *fp;
	char* env_c = bstr2cstr(env, '\0');
	bdestroy(env);
	bstring env_cxt;
	if (NULL != (fp = fopen (env_c, "r"))) {
		env_cxt = bread ((bNread) fread, fp);
		fclose (fp);
	} else {
		bcstrfree(env_c);
		fclose(fp);
		return 0;
	}
	bcstrfree(env_c);
	struct bstrList *envs = bsplit(env_cxt, '\n');
	bdestroy(env_cxt);
// match file
	bstring env_row;
	int count = 0;
	for (int i=0; i < envs->qty - 1; i++) {
		env_row = bformat("/var/lib/auch/packages/%s%s", envs->entry[i]->data, virt_path);
		char* env_row_c = bstr2cstr(env_row, '\n');
		if (access(env_row_c, 0)==0) {
			DIR *dp;
			if ((dp = opendir(env_row_c)) != NULL) {  
    			struct dirent *entry;
    			while ((entry = readdir(dp)) != NULL) {
					bstring p = bformat("%s/%s", virt_path, entry->d_name);
					phy_components[count] = bstr2cstr(p,'\0');
					bdestroy(p);
					count++;
    			}
    		}
    		closedir(dp);
		}
		bcstrfree(env_row_c);
	}
	bdestroy(env_row);
	return count;
}

char* vrfs_resolve(const char *virt_path, pid_t pid) {
// get env file name
	bstring env = vrfs_resolve_index(pid);
	if (env!=NULL) {
		char* env_c = bstr2cstr(env, '\0');
		printf("resolve file env - DBG: %s\n",env_c);
		bcstrfree(env_c);
	} else {
		printf("resolve file env - DBG: no AUCH_ENV found\n");
		bdestroy(env);
		return NULL;
	}
// get env file content
	FILE *fp;
	char* env_c = bstr2cstr(env, '\0');
	bdestroy(env);
	bstring env_cxt;
	if (NULL != (fp = fopen (env_c, "r"))) {
		env_cxt = bread ((bNread) fread, fp);
		fclose (fp);
	} else {
		bcstrfree(env_c);
		fclose(fp);
		return NULL;
	}
	bcstrfree(env_c);
	struct bstrList *envs = bsplit(env_cxt, '\n');
	bdestroy(env_cxt);
// match file
	bstring env_row;
	for (int i=0; i < envs->qty - 1; i++) {
		env_row = bformat("/var/lib/auch/packages/%s%s", envs->entry[i]->data, virt_path);
		char* env_row_c = bstr2cstr(env_row, '\n');
		if (access(env_row_c, 0)==0) {
			bdestroy(env_row);
			return env_row_c;
		}
		bcstrfree(env_row_c);
	}
	bdestroy(env_row);
	return NULL;
}
