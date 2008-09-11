/* Copyright (C) 1993, 96, 97, 98, 99, 2000, 2008
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

#ifndef _SYS_STAT_H
# error "Never include <bits/stat.h> directly; use <sys/stat.h> instead."
#endif

#include <bits/wordsize.h>

/* Length of array allocated for file system type name.  */
#define _ST_FSTYPSZ	16

/* Structure describing file characteristics.  */
struct stat
  {
    __dev_t st_dev;
#if __WORDSIZE == 32
    long int st_pad1[3];
#endif
#ifndef __USE_FILE_OFFSET64
    __ino_t st_ino;		/* File serial number.		*/
#else
    __ino64_t st_ino;		/* File serial number.		*/
#endif
    __mode_t st_mode;		/* File mode.  */
    __nlink_t st_nlink;		/* Link count.  */
    __uid_t st_uid;		/* User ID of the file's owner.	*/
    __gid_t st_gid;		/* Group ID of the file's group.*/
    __dev_t st_rdev;	/* Device number, if device.  */
#if __WORDSIZE == 32
    long int st_pad2[2];
#endif
#ifndef __USE_FILE_OFFSET64
    __off_t st_size;		/* Size of file, in bytes.  */
#else
    __off64_t st_size;		/* Size of file, in bytes.  */
#endif
#if __WORDSIZE == 32 && !defined(__USE_FILE_OFFSET64)
    long int st_pad3;
#endif
#ifdef __USE_MISC
    struct timespec st_atim;		/* Time of last access.  */
    struct timespec st_mtim;		/* Time of last modification.  */
    struct timespec st_ctim;		/* Time of last status change.  */
# define st_atime st_atim.tv_sec	/* Backward compatibility.  */
# define st_mtime st_mtim.tv_sec
# define st_ctime st_ctim.tv_sec
#else
    __time_t st_atime;		/* Time of last access.  */
    unsigned long int st_atime_usec;
    __time_t st_mtime;		/* Time of last modification.  */
    unsigned long int st_mtime_usec;
    __time_t st_ctime;		/* Time of last status change.  */
    unsigned long int st_ctime_usec;
#endif
    __blksize_t st_blksize;	/* Optimal block size for I/O.  */
#define	_STATBUF_ST_BLKSIZE	/* Tell code we have this member.  */

#ifndef __USE_FILE_OFFSET64
    __blkcnt_t st_blocks;	/* Number of 512-byte blocks allocated.  */
#else
    __blkcnt64_t st_blocks;	/* Number of 512-byte blocks allocated.  */
#endif
    char st_fstype[_ST_FSTYPSZ];
#if __WORDSIZE == 32
    long int st_pad4[8];
#endif
  };

#ifdef _SYSCALL32
#include <sys/types32.h>

struct stat32
  {
	__dev_t st_dev;
	__int32_t st_pad1[3];
	__ino_t st_ino;
	__mode_t st_mode;
	__nlink_t st_nlink;
	__uid_t st_uid;
	__gid_t st_gid;
	__dev_t st_rdev;
	__int_t st_pad2[2];
	__off_t st_size;
	__int32_t st_pad3;
	struct timespec32 st_atim;
	struct timespec32 st_mtim;
	struct timespec32 st_ctim;
	__int32_t st_blksize;
	__blkcnt_t st_blocks;
	char st_fstype[_ST_FSTYPSZ];
	__int32_t st_pad4[8];
  };
#endif /* _SYSCALL32 */

#ifdef __USE_LARGEFILE64
/* struct stat64 has the shape as stat */
struct stat64
  {
    __dev_t st_dev;			/* Device */
#if __WORDSIZE == 32
    long int st_pad1[3];
#endif
    __ino64_t st_ino;			/* File serial number */
    __mode_t st_mode;			/* File mode */
    __nlink_t st_nlink;			/* Link count */
    __uid_t st_uid;				/* User ID of the file's owner. */
    __gid_t st_gid;				/* Group ID of the file's group.*/
    __dev_t st_rdev;			/* Device number, if device */
#if __WORDSIZE == 32
    long int st_pad2[2];
#endif
    __off64_t st_size;			/* Size of file, in bytes. */
#ifdef __USE_MISC
    struct timespec st_atim;		/* Time of last access.  */
    struct timespec st_mtim;		/* Time of last modification.  */
    struct timespec st_ctim;		/* Time of last status change.  */
# define st_atime st_atim.tv_sec	/* Backward compatibility.  */
# define st_mtime st_mtim.tv_sec
# define st_ctime st_ctim.tv_sec
#else
    __time_t st_atime;			/* Time of last access */
    unsigned long int st_atime_usec;
    __time_t st_mtime;			/* Time of last modification */
    unsigned long int st_mtime_usec;
    __time_t st_ctime;			/* Time of last status change */
    unsigned long int st_ctime_usec;
#endif
    __blksize_t st_blksize;
    __blkcnt64_t st_blocks;
    char st_fstype[_ST_FSTYPSZ];
#if __WORDSIZE == 32
    long int st_pad4[8];
#endif
};
#endif

#ifdef _SYSCALL32

#include <sys/isa_defs.h>

#if _LONG_LONG_ALIGNMENT == 8 && _LONG_LONG_ALIGNMENT_32 == 4
# pragma pack(4)
#endif

struct stat64_32
  {
	dev32_t st_dev;
	int32_t st_pad1[3];
	ino64_t st_ino;
	mode32_t st_mode;
	nlink32_t st_nlink;
	uid32_t st_uid;
	gid32_t st_gid;
	dev32_t st_rdev;
	int32_t st_pad2[2];
	off64_t st_size;
	struct timespec32 st_atim;
	struct timespec32 st_mtim;
	struct timespec32 st_ctim;
	int32_t st_blksize;
	blkcnt64_t st_blocks;
	char st_fstype[_ST_FSTYPSZ];
	int32_t st_pad4[8];
  };

#if _LONG_LONG_ALIGNMENT == 8 && _LONG_LONG_ALIGNMENT_32 == 4
# pragma pack()
#endif

#endif /* _SYSCALL32 */

/* Tell code we have these members.  */
#define	_STATBUF_ST_BLKSIZE
#define _STATBUF_ST_RDEV

/* Encoding of the file mode.  */

#define	__S_IFMT	0xF000	/* These bits determine file type.  */

/* File types.  */
#define	__S_IFDIR	0x4000	/* Directory.  */
#define	__S_IFCHR	0x2000	/* Character device.  */
#define	__S_IFBLK	0x6000	/* Block device.  */
#define	__S_IFREG	0x8000	/* Regular file.  */
#define	__S_IFIFO	0x1000	/* FIFO.  */
#define	__S_IFLNK	0xA000	/* Symbolic link.  */
#define	__S_IFSOCK	0xC000	/* Socket.  */
#define   S_IFDOOR	0xD000	/* Door.	*/
#define   S_IFPORT	0xE000	/* Event port.	*/

/* POSIX.1b objects.  */
#define __S_TYPEISMQ(buf) (0)
#define __S_TYPEISSEM(buf) (0)
#define __S_TYPEISSHM(buf) (0)

/* Protection bits.  */

#define	__S_ISUID	0x800	/* Set user ID on execution.  */
#define	__S_ISGID	0x400	/* Set group ID on execution.  */
#define	__S_ISVTX	0x200	/* Save swapped text after use (sticky).  */
#define	__S_IREAD	00400	/* Read by owner.  */
#define	__S_IWRITE	00200	/* Write by owner.  */
#define	__S_IEXEC	00100	/* Execute by owner.  */

#define _R3_MKNOD_VER	1	/* SVR3.0 mknod */
#define _MKNOD_VER		2	/* current version of mknod */
#define _R3_STAT_VER	1	/* SVR3.0 stat */
#define _STAT_VER		2	/* current version of stat */

#define S_ISDOOR(mode)  (((mode) & 0xF000) == S_IFDOOR)
#define S_ISPORT(mode)  (((mode) & 0xF000) == S_IFPORT)
