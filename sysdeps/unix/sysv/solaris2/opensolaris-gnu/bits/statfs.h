/* Copyright (C) 1997, 1998, 2000, 2002, 2003, 2008
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

#ifndef _SYS_STATFS_H
# error "Never include <bits/statfs.h> directly; use <sys/statfs.h> instead."
#endif

#include <bits/types.h>

struct statfs
  {
    short int f_fstyp;
    long int f_bsize;
    long int f_frsize;
    long int f_blocks;
    long int f_bfree;
#ifndef __USE_FILE_OFFSET64
    __ino64_t f_files;
    __ino64_t f_ffree;
#else
    __ino64_t f_files;
    __ino64_t f_ffree;
#endif
    char f_fname[6];
    char f_fpack[6];
  };

/* There is no statfs64 on OpenSolaris. */
struct statfs64;

/* Tell code we have these members.  */
#define _STATFS_F_NAMELEN
#define _STATFS_F_FRSIZE
