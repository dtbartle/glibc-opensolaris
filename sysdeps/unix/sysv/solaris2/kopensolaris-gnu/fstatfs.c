#define STATFS_FUNC __fstatfs
#define STATFS_STRUCT struct statfs
#define STATVFS_FUNC __fstatvfs
#define STATVFS_STRUCT struct statvfs
#define STATFS_ARG int
#include "sysdeps/unix/sysv/solaris2/kopensolaris-gnu/statfs_common.c"
weak_alias (__fstatfs, fstatfs)
