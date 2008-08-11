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

DECLARE_INLINE_SYSCALL (ssize_t, sendmsg, int s, const struct msghdr *msg,
    int flags);

ssize_t
__sendmsg (fd, message, flags)
     int fd;
     const struct msghdr *message;
     int flags;
{
  struct sigaction act;
  sigset_t mask;
  if (flags & MSG_NOSIGNAL)
    {
      if (__send_msg_nosignal_pre(&act, &mask) != 0)
        return -1;
    }

  int result = INLINE_SYSCALL(sendmsg, 3, fd, message,
    (flags & ~MSG_NOSIGNAL) | MSG_XPG4_2);

  if(flags & MSG_NOSIGNAL)
    assert (__send_msg_nosignal_post(&act, &mask) == 0);

  return result;
}

weak_alias (__sendmsg, sendmsg)
