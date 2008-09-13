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

#include <sysdep-cancel.h>
#include <not-cancel.h>
#include <inline-syscall.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#ifndef OPEN_FUNC_PRE_FILE_PARAM_DECLS
# define OPEN_FUNC_PRE_FILE_PARAM_DECLS
#endif
#ifndef OPEN_FUNC_PRE_FILE_ARGS
# define OPEN_FUNC_PRE_FILE_ARGS
#endif

/* rtld doesn't use O_DIRECT or O_DIRECTORY so just use the syscall */

int
OPEN_NOT_CANCEL_FUNC_NAME (OPEN_FUNC_PRE_FILE_PARAM_DECLS
        const char *file, int oflag, mode_t mode)
{
  /* ensure we don't pass O_DIRECT and O_DIRECTORY down */
  int saved_oflag = oflag;
  oflag = oflag & ~(O_DIRECT | O_DIRECTORY);

  if (saved_oflag & O_DIRECT)
    oflag |= O_SYNC | O_RSYNC;

  int fd = OPEN_FUNC_SYSCALL;
  if (fd == -1)
    return -1;

  /* verify that opened file was a directory */
  if (saved_oflag & O_DIRECTORY)
    {
      OPEN_FUNC_STAT_BUF buf;
      int res = OPEN_FUNC_STAT;
      if (res == -1)
        {
          close_not_cancel_no_status (fd);
          return -1;
        }
      if (!S_ISDIR (buf.st_mode))
        {
          close_not_cancel_no_status (fd);
          __set_errno (ENOTDIR);
          return -1;
        }
    }

  /* enable direct i/o via _FIODIRECTIO */
  if (saved_oflag & O_DIRECT)
    {
      int res = ioctl (fd, _FIODIRECTIO, DIRECTIO_ON);
      if (res == -1)
        {
          close_not_cancel_no_status(fd);
          return -1;
        }
    }

  return fd;
}

int
OPEN_FUNC_NAME (OPEN_FUNC_PRE_FILE_PARAM_DECLS
        const char *file, int oflag, ...)
{
  int mode = 0;

  if (oflag & O_CREAT)
    {
      va_list arg;
      va_start (arg, oflag);
      mode = va_arg (arg, int);
      va_end (arg);
    }

  if (SINGLE_THREAD_P)
    return OPEN_NOT_CANCEL_FUNC_NAME (OPEN_FUNC_PRE_FILE_ARGS
        file, oflag, mode);

  int oldtype = LIBC_CANCEL_ASYNC ();

  int res = OPEN_NOT_CANCEL_FUNC_NAME (OPEN_FUNC_PRE_FILE_ARGS
      file, oflag, mode);

  LIBC_CANCEL_RESET (oldtype);

  return res;
}
