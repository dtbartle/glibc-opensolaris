/* Copyright (C) 1991,92,93,1996-2002,2006,2008 Free Software Foundation, Inc.
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

#define __TTYNAME_NO_CHECKS
#define __ASSUME_PROC_SELF_FD_NOT_SYMLINK
#include <sysdeps/unix/sysv/linux/ttyname.c>

char *
_ttyname_dev (dev_t rdev, char *buffer, size_t buflen)
{
  struct stat64 st;
  int dostat = 0;
  char *name;
  int save = errno;
  struct termios term;

  if (__xstat64 (_STAT_VER, "/dev/pts", &st) == 0 && S_ISDIR (st.st_mode))
    {
      dostat = 1;
      name = getttyname ("/dev/pts", rdev, -1, save, &dostat);
    }
  else
    {
      __set_errno (save);
      name = NULL;
    }

  if (!name && dostat != -1)
    {
      dostat = 1;
      name = getttyname ("/dev", rdev, -1, save, &dostat);
    }

  return name;
}
