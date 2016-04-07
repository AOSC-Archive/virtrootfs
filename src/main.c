#include "vr_fuse.h"
#include "vr_ops.h"

static struct fuse_operations vr_ops = {
};

int main(int argc, char **argv)
{
	umask(0);
	return fuse_main (argc, argv, &vr_ops, NULL);
}
