/* Header file for mounting/unmount OpenSolaris filesystems.
   Copyright (C) 1996,1997,1998,1999,2000,2004,2008
    Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/* This is taken from /usr/include/linux/fs.h.  */

#ifndef _SYS_MOUNT_H
#define _SYS_MOUNT_H	1

#include <features.h>
#include <sys/ioctl.h>

#define BLOCK_SIZE	1024
#define BLOCK_SIZE_BITS	10


/* These are the fs-independent mount-flags: up to 16 flags are
   supported  */
enum
{
  MS_RDONLY = 1,		/* Mount read-only.  */
#define MS_RDONLY	MS_RDONLY
  MS_FSS = 2,		/* Old mount.  */
#define MS_FSS	MS_FSS
  MS_DATA = 4 ,		/* 6-argument mount.  */
#define MS_DATA	MS_DATA
  MS_NOSUID = 16,		/* Ignore suid and sgid bits.  */
#define MS_NOSUID	MS_NOSUID
  MS_REMOUNT = 32,		/* Alter flags of a mounted FS.  */
#define MS_REMOUNT	MS_REMOUNT
  MS_NOTRUNC = 64,		/* Return ENAMETOOLONG for long filenames.  */
#define MS_NOTRUNC	MS_NOTRUNC
  MS_OVERLAY = 128,		/* Allow overlay mounts.  */
#define MS_OVERLAY	MS_OVERLAY
  MS_OPTIONSTR = 256,		/* Data is a an in/out option string.  */
#define MS_OPTIONSTR	MS_OPTIONSTR
  MS_GLOBAL = 512,		/* Clustering: Mount into global name space.  */
#define MS_GLOBAL	MS_GLOBAL
  MS_FORCE = 1024,		/* Forced unmount.  */
#define MS_FORCE	MS_FORCE
  MS_NOMNTTAB = 2048		/* Don't show mount in mnttab.  */
#define MS_NOMNTTAB	MS_NOMNTTAB
};


__BEGIN_DECLS

/* Mount a filesystem.  */
extern int mount (__const char *__spec, __const char *__dir,
		  int __mflag_, __const char *__fstype, __const void *__dataptr,
		  int __datalen, char *__optptr, int __optlen) __THROW;

/* Unmount a filesystem.  */
extern int umount (__const char *__file) __THROW;

/* Unmount a filesystem.  Force unmounting if FLAG is set to MS_FORCE.  */
extern int umount2 (__const char *__file, int __flag) __THROW;

__END_DECLS

#endif /* _SYS_MOUNT_H */
