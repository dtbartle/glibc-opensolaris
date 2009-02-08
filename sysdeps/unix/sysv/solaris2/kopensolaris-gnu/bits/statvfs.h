/* Copyright (C) 1997,1998,2000,2001,2002,2006,2008
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

#ifndef _SYS_STATVFS_H
# error "Never include <bits/statvfs.h> directly; use <sys/statvfs.h> instead."
#endif

#include <bits/types.h>  /* For __fsblkcnt_t and __fsfilcnt_t.  */
#include <bits/wordsize.h>
#include <features.h>

#define _FSTYPSZ 16
#ifdef __USE_MISC
# define FSTYPSZ	_FSTYPSZ
#endif

typedef struct statvfs
{
    unsigned long int f_bsize;
    unsigned long int f_frsize;
#if defined(__USE_FILE_OFFSET64) || defined(__USE_LARGEFILE64)
    __fsblkcnt64_t f_blocks;
    __fsblkcnt64_t f_bfree;
	__fsblkcnt64_t f_bavail;
    __fsfilcnt64_t f_files;
    __fsfilcnt64_t f_ffree;
    __fsfilcnt64_t f_favail;
#else
    __fsblkcnt_t f_blocks;
    __fsblkcnt_t f_bfree;
    __fsblkcnt_t f_bavail;
    __fsfilcnt_t f_files;
    __fsfilcnt_t f_ffree;
    __fsfilcnt_t f_favail;
#endif
    unsigned long int f_fsid;
    char f_basetype[_FSTYPSZ];
    unsigned long int f_flag;
    unsigned long int f_namemax;
    char f_fstr[32];
#if __WORDSIZE == 32
    unsigned long f_filler[16];
#endif
} statvfs_t;

#ifdef _SYSCALL32
typedef struct statvfs32
{
	__uint32_t f_bsize;
	__uint32_t f_frsize;
	__fsblkcnt_t f_blocks;
	__fsblkcnt_t f_bfree;
	__fsblkcnt_t f_bavail;
	__fsfilcnt_t f_files;
	__fsfilcnt_t f_ffree;
	__fsfilcnt_t f_favail;
	__uint32_t f_fsid;
	char f_basetype[_FSTYPSZ];
	__uint32_t f_flag;
	__uint32_t f_namemax;
	char f_fstr[32];
	__uint32_t f_filler[16];
} statvfs32_t;
#endif

#ifdef __USE_LARGEFILE64
typedef struct statvfs64
{
    unsigned long int f_bsize;
    unsigned long int f_frsize;
    __fsblkcnt64_t f_blocks;
    __fsblkcnt64_t f_bfree;
    __fsblkcnt64_t f_bavail;
    __fsfilcnt64_t f_files;
    __fsfilcnt64_t f_ffree;
    __fsfilcnt64_t f_favail;
    unsigned long int f_fsid;
    char f_basetype[_FSTYPSZ];
    unsigned long int f_flag;
    unsigned long int f_namemax;
    char f_fstr[32];
#if __WORDSIZE == 32
    unsigned long f_filler[16];
#endif
} statvfs64_t;
#endif

#ifdef _SYSCALL32
typedef struct statvfs64_32
{
	__uint32_t f_bsize;
	__uint32_t f_frsize;
	__fsblkcnt64_t f_blocks;
	__fsblkcnt64_t f_bfree;
	__fsblkcnt64_t f_bavail;
	__fsfilcnt64_t f_files;
	__fsfilcnt64_t f_ffree;
	__fsfilcnt64_t f_favail;
	__uint32_t f_fsid;
	char f_basetype[_FSTYPSZ];
	__uint32_t f_flag;
	__uint32_t f_namemax;
	char f_fstr[32];
	__uint32_t f_filler[16];
} statvfs64_32_t;
#endif

/* Definitions for the flag in `f_flag'.  These definitions should be
   kept in sync with the definitions in <sys/mount.h>.  */
enum
{
  ST_RDONLY = 1,		/* Mount read-only.  */
#define ST_RDONLY	ST_RDONLY
  ST_NOSUID = 2,		/* Ignore suid and sgid bits.  */
#define ST_NOSUID	ST_NOSUID
  ST_NOTRUNC = 4		/* Don't truncate long files.  */
#define ST_NOTRUNC	ST_NOTRUNC
};
