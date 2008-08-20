/* Copyright (C) 2005, 2006, 2008 Free Software Foundation, Inc.
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

#include <inline-syscall.h>
#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <sys/stat.h>
#include <bp-checks.h>

DECLARE_INLINE_SYSCALL (int, fstatat, int fd, const char *name,
    struct stat *sb, int flags);

int
__fxstatat (int vers, int fd, const char *filename, struct stat *buf, int flag)
{
  if (vers != _STAT_VER)
    {
      __set_errno(ENOSYS);
      return -1;
    }

  return INLINE_SYSCALL (fstatat, 2, fd, filename, CHECK_1 (buf), flag);
}
libc_hidden_def (__fxstatat)
