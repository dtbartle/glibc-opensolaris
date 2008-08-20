/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>, 2008.

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

#include <inline-syscall.h>

DECLARE_INLINE_SYSCALL (int, openat64, int dirfd, const char *pathname,
    int flags, mode_t mode);

#define OPEN_FUNC_NAME					__openat64
#define OPEN_NOT_CANCEL_FUNC_NAME		openat64_not_cancel
#define OPEN_FUNC_SYSCALL				INLINE_SYSCALL (openat64, 4, dirfd, file, oflag, mode)
#define OPEN_FUNC_PRE_FILE_PARAM_DECLS	int dirfd,
#define OPEN_FUNC_PRE_FILE_ARGS			dirfd,
#define OPEN_FUNC_STAT					fstat64(fd, &buf)
#define OPEN_FUNC_STAT_BUF				struct stat64
#include "open-func.c"

libc_hidden_def (__openat64)
weak_alias (__openat64, openat64)
