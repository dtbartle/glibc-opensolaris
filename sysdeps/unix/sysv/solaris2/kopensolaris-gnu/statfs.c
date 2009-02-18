#define STATFS_FUNC __statfs
#define STATFS_STRUCT struct statfs
#define STATVFS_FUNC __statvfs
#define STATVFS_STRUCT struct statvfs
#define STATFS_ARG const char *
#include "sysdeps/unix/sysv/solaris2/kopensolaris-gnu/statfs_common.c"
libc_hidden_def (__statfs)
weak_alias (__statfs, statfs)
