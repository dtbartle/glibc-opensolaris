#define STATFS_FUNC __fstatfs64
#define STATFS_STRUCT struct statfs64
#define STATVFS_FUNC __fstatvfs64
#define STATVFS_STRUCT struct statvfs64
#define STATFS_ARG int
#include "sysdeps/unix/sysv/solaris2/kopensolaris-gnu/statfs_common.c"
weak_alias (__fstatfs64, fstatfs64)
