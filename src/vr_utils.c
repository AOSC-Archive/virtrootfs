#include "vr_utils.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int vr_is_dir (const char *path)
{
	struct stat buf;
	if (!lstat (path, &buf))
		return (buf.st_mode & S_IFDIR) == S_IFDIR;
	return 0; /* When an error occured, we return 0, and lstat will set errno */
}
