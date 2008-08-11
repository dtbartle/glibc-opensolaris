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
#include <sys/sendfile.h>
#include <errno.h>

DECLARE_INLINE_SYSCALL (ssize_t, sendfilev, int fildes,
    const struct sendfilevec *vec, int sfvcnt, size_t *xferred);

ssize_t
sendfile (int out_fd, int in_fd, off_t *offset, size_t count)
{
  if(count > 0 && offset == NULL)
    {
      __set_errno(EINVAL);
      return -1;
    }

  sendfilevec_t sfv;
  sfv.sfv_fd = in_fd;
  sfv.sfv_flag = 0;
  sfv.sfv_off = *offset;
  sfv.sfv_len = count;

  /* call sendfilev */
  size_t xferred = 0;
  int result = INLINE_SYSCALL(sendfilev, 4, out_fd, &sfv, 1, &xferred);
      return -1;
  *offset += xferred;

  return result;
}
