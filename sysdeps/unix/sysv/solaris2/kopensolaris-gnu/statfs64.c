#define STATFS_FUNC __statfs64
#define STATFS_STRUCT struct statfs64
#define STATVFS_FUNC __statvfs64
#define STATVFS_STRUCT struct statvfs64
#define STATFS_ARG const char *
#include "sysdeps/unix/sysv/solaris2/kopensolaris-gnu/statfs_common.c"
weak_alias (__statfs64, statfs64)
