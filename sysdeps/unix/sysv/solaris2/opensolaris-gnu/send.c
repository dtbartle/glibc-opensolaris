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
#include <sys/socket.h>
#include <assert.h>
#include "send_msg_nosignal.h"

DECLARE_INLINE_SYSCALL (ssize_t, send, int s, const void *buf, size_t len,
    int flags);

ssize_t
__send (fd, buf, n, flags)
     int fd;
     __const __ptr_t buf;
     size_t n;
     int flags;
{
  struct sigaction act;
  sigset_t mask;
  if (flags & MSG_NOSIGNAL)
    {
      if (__send_msg_nosignal_pre (&act, &mask) != 0)
        return -1;
    }

  int result = INLINE_SYSCALL (send, 4, fd, buf, n, flags & ~MSG_NOSIGNAL);

  if (flags & MSG_NOSIGNAL)
    assert (__send_msg_nosignal_post (&act, &mask) == 0);

  return result;
}

libc_hidden_def (__send)
weak_alias (__send, send)
