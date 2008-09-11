/* Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_TYPES32_H
#define _SYS_TYPES32_H

#include <bits/types.h>

typedef __uint32_t	caddr32_t;
typedef __int32_t	daddr32_t;
typedef __int32_t	off32_t;
typedef __uint32_t	ino32_t;
typedef __int32_t	blkcnt32_t;
typedef __uint32_t	fsblkcnt32_t;
typedef __uint32_t	fsfilcnt32_t;
typedef __int32_t	id32_t;
typedef __uint32_t	major32_t;
typedef __uint32_t	minor32_t;
typedef __int32_t	key32_t;
typedef __uint32_t	mode32_t;
typedef __uint32_t	uid32_t;
typedef __uint32_t	gid32_t;
typedef __uint32_t	nlink32_t;
typedef __uint32_t	dev32_t;
typedef __int32_t	pid32_t;
typedef __uint32_t	size32_t;
typedef __int32_t	ssize32_t;
typedef __int32_t	time32_t;
typedef __int32_t	clock32_t;

struct timeval32
  {
	time32_t tv_sec;
	__int32_t tv_usec;
  };

struct timespec32
  {
	time32_t tv_sec;
	__int32_t tv_nsec;
  };

#endif /* _SYS_TYPES32_H */
