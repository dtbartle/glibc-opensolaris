/* O_*, F_*, FD_* bit values for OpenSolaris.
   Copyright (C) 2001, 2002, 2004, 2006, 2007, 2008
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

#ifndef _FCNTL_H
# error "Never use <bits/fcntl.h> directly; include <fcntl.h> instead."
#endif

#include <sys/types.h>
#include <bits/wordsize.h>
#ifdef __USE_GNU
# include <bits/uio.h>
#endif


/* open/fcntl */
#define	O_RDONLY	0
#define	O_WRONLY	1
#define	O_RDWR		2
#define	O_ACCMODE	3
#define	O_NDELAY	0x04
#define	O_APPEND	0x08
#define	O_SYNC		0x10
#define	O_NONBLOCK	0x80
#define	O_CREAT		0x100
#define	O_TRUNC		0x200
#define	O_EXCL		0x400
#define	O_NOCTTY	0x800
#define	O_PRIV		0x1000
#define	O_XATTR		0x4000
#define	O_NOFOLLOW	0x20000
#define	O_NOLINKS	0x40000

#if defined __USE_POSIX199309 || defined __USE_UNIX98
# define O_DSYNC    0x40  /* Synchronize data.  */
# define O_RSYNC    0x8000  /* Synchronize read operations.  */
#endif
#define O_FSYNC		O_SYNC

#ifdef __USE_GNU
#define O_DIRECT	0x1000000
#define O_DIRECTORY	0x2000000
#endif

#ifdef __USE_LARGEFILE64
# if __WORDSIZE == 64
#  define O_LARGEFILE   0
# else
#  define O_LARGEFILE   0x2000
# endif
#endif

/* Values for the second argument to `fcntl'.  */
#define F_DUPFD		0	/* Duplicate file descriptor.  */
#define F_GETFD		1	/* Get file descriptor flags.  */
#define F_SETFD		2	/* Set file descriptor flags.  */
#define F_GETFL		3	/* Get file status flags.  */
#define F_SETFL		4	/* Set file status flags.  */
#if __WORDSIZE == 64
# define F_GETLK	14	/* Get record locking info.  */
# define F_SETLK	6	/* Set record locking info (non-blocking).  */
# define F_SETLKW	7	/* Set record locking info (blocking).  */
# define F_ALLOCSP	10	/* Allocate file space.  */
# define F_FREESP	11	/* Free file space.  */
# define F_SETLK_NBMAND	42	/* Private.  */
/* Not necessary, we always have 64-bit offsets.  */
# define F_GETLK64	F_GETLK	/* Get record locking info.  */
# define F_SETLK64	F_SETLK	/* Set record locking info (non-blocking).  */
# define F_SETLKW64	F_SETLKW	/* Set record locking info (blocking).  */
# define F_ALLOCSP64	F_ALLOCSP	/* Allocate file space.  */
# define F_FREESP64	F_FREESP	/* Free file space.  */
# define F_SETLK64_NBMAND	F_SETLK_NBMAND	/* Private.  */
#else
# ifndef __USE_FILE_OFFSET64
#  define F_GETLK	14	/* Get record locking info.  */
#  define F_SETLK	6	/* Set record locking info (non-blocking).  */
#  define F_SETLKW	7	/* Set record locking info (blocking).  */
#  define F_ALLOCSP	10	/* Allocate file space.  */
#  define F_FREESP	11	/* Free file space.  */
#  define F_SETLK_NBMAND	42	/* Private.  */
# else
#  define F_GETLK	F_GETLK64	/* Get record locking info.  */
#  define F_SETLK	F_SETLK64	/* Set record locking info (non-blocking).*/
#  define F_SETLKW	F_SETLKW64	/* Set record locking info (blocking).  */
#  define F_ALLOCSP	F_ALLOCSP64	/* Allocate file space.  */
#  define F_FREESP	F_FREESP64	/* Free file space.  */
#  define F_SETLK_NBMAND	F_SETLK64_NBMAND	/* Private.  */
# endif
# define F_GETLK64	33	/* Get record locking info.  */
# define F_SETLK64	34	/* Set record locking info (non-blocking).  */
# define F_SETLKW64	35	/* Set record locking info (blocking).  */
# define F_ALLOCSP64	28	/* Allocate file space.  */
# define F_FREESP64	27	/* Free file space.  */
# define F_SETLK64_NBMAND	44	/* Private.  */
#endif

/* OpenSolaris-specific */
#define F_GETXFL	45
#define F_CHKFL		8
#define F_DUP2FD	9
#define F_ISSTREAM	13
#define F_PRIV		15
#define F_NPRIV		16
#define F_QUOTACTL	17
#define F_BLOCKS	18
#define F_BLKSIZE	19
#define F_GETOWN	23
#define F_SETOWN	24
#define F_REVOKE	25
#define F_HASREMOTELOCKS	26

#define F_SHARE		40
#define F_UNSHARE	41
#define F_SHARE_NBMAND	43

typedef struct fshare
{
    short f_access;
	short f_deny;
    int	f_id;
} fshare_t;

/* f_access values */
#define F_RDACC		0x1
#define F_WRACC		0x2
#define F_RWACC		0x3
#define F_RMACC		0x4
#define F_MDACC		0x20

/* f_deny values */
#define F_NODNY		0x0
#define F_RDDNY		0x1
#define F_WRDNY		0x2
#define F_RWDNY		0x3
#define F_RMDNY		0x4
#define F_COMPAT	0x8
#define F_MANDDNY	0x10

#define F_BADFD		46

/* For F_[GET|SET]FD.  */
# define FD_CLOEXEC	1	/* actually anything with low bit set goes */

/* For posix fcntl() and `l_type' field of a `struct flock' for lockf().  */
# define F_RDLCK	1	/* Read lock.  */
# define F_WRLCK	2	/* Write lock.  */
# define F_UNLCK	3	/* Remove lock.  */
/* OpenSolaris-specific */
#define F_UNLKSYS	4

struct flock
  {
    short int l_type;	/* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.	*/
    short int l_whence;	/* Where `l_start' is relative to (like `lseek').  */
#ifndef __USE_FILE_OFFSET64
    __off_t l_start;	/* Offset where the lock begins.  */
    __off_t l_len;	/* Size of the locked area; zero means until EOF.  */
#else
    __off64_t l_start;	/* Offset where the lock begins.  */
    __off64_t l_len;	/* Size of the locked area; zero means until EOF.  */
#endif
    int l_sysid;
    __pid_t l_pid;	/* Process holding the lock.  */
    long l_pad[4];
  };

#ifdef _SYSCALL32
typedef struct flock32
  {
	__int16_t l_type;
	__int16_t l_whence;
	__off_t l_start;
	__off_t l_len;
	__int32_t l_sysid;
	__pid_t l_pid;
	__int32_t l_pad[4];
  } flock32_t;
#endif

#ifdef __USE_LARGEFILE64
struct flock64
  {
    short int l_type;	/* Type of lock: F_RDLCK, F_WRLCK, or F_UNLCK.	*/
    short int l_whence;	/* Where `l_start' is relative to (like `lseek').  */
    __off64_t l_start;	/* Offset where the lock begins.  */
    __off64_t l_len;	/* Size of the locked area; zero means until EOF.  */
    int l_sysid;
    __pid_t l_pid;	/* Process holding the lock.  */
    long l_pad[4];
  };
#endif

/* OpenSolaris direct i/o */
#define DIRECTIO_OFF	(0)
#define DIRECTIO_ON		(1)

/* OpenSolaris-specific seek flags */
#define SEEK_DATA  3
#define SEEK_HOLE  4

/* at-file support */
#ifdef __USE_ATFILE
# define AT_FDCWD              0xffd19553   /* Special value used to indicate
                                          the *at functions should use the
                                          current working directory. */
# define AT_SYMLINK_NOFOLLOW   0x1000  /* Do not follow symbolic links.  */
# define AT_REMOVEDIR          0x1     /* Remove directory instead of
                                          unlinking file.  */
#endif

/* Define some more compatibility macros to be backward compatible with
   BSD systems which did not managed to hide these kernel macros.  */
#ifdef  __USE_BSD
# define FOPEN		0xffffffff
# define FREAD		0x01
# define FWRITE		0x02
# define NDELAY		0x04
# define FNDELAY	NDELAY
# define FAPPEND	0x08
# define FSYNC		0x10
# define FFSYNC		FSYNC
# define FREVOKED	0x20
# define FDSYNC		0x40
# define FNONBLOCK	0x80
# define FCREAT		0x0100
# define FTRUNC		0x0200
# define FEXCL		0x0400
# define FASYNC		0x1000
# define FOFFMAX	0x2000
# define FXATTR		0x4000
# define FNOCTTY	0x0800
# define FRSYNC		0x8000
# define FNODSYNC	0x10000
# define FNOFOLLOW	0x20000
# define FNOLINKS	0x40000
# define FIGNORECASE	0x80000
# define FXATTRDIROPEN	0x100000
#endif /* Use BSD.  */

/* Advise to `posix_fadvise'.  */
#ifdef __USE_XOPEN2K
# define POSIX_FADV_NORMAL	0 /* No further special treatment.  */
# define POSIX_FADV_RANDOM	1 /* Expect random page references.  */
# define POSIX_FADV_SEQUENTIAL	2 /* Expect sequential page references.  */
# define POSIX_FADV_WILLNEED	3 /* Will need these pages.  */
# define POSIX_FADV_DONTNEED	4 /* Don't need these pages.  */
# define POSIX_FADV_NOREUSE	5 /* Data will be accessed once.  */
#endif
