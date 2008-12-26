/* Change the protections of file relative to open directory.  OpenSolaris version.
   Copyright (C) 2006, 2008 Free Software Foundation, Inc.
   Contributed by Robert Millan <rmh@aybabtu.com>
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

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <not-cancel.h>

int
fchmodat (dirfd, file, mode, flag)
     int dirfd;
     const char *file;
     mode_t mode;
     int flag;
{
  int fd, ret;

  if (file == NULL || (flag & ~AT_SYMLINK_NOFOLLOW) != 0)
    {
      __set_errno (EINVAL);
      return -1;
    }

  if (fd < 0 && fd != AT_FDCWD)
    {
      __set_errno (EBADF);
      return -1;
    }

  fd = openat (dirfd, file, 0);
  if (fd == -1)
    return -1;

  ret = fchmod (fd, mode);
  close_not_cancel_no_status (fd);

  return ret;
}
