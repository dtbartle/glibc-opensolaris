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
#include <socket_priv.h>

DECLARE_INLINE_SYSCALL (ssize_t, sendto, int s, const void *buf, size_t len,
    int flags, __CONST_SOCKADDR_ARG to, socklen_t tolen);

ssize_t
__sendto (fd, buf, n, flags, addr, addr_len)
     int fd;
     __const __ptr_t buf;
     size_t n;
     int flags;
     __CONST_SOCKADDR_ARG addr;
     socklen_t addr_len;
{
  if (flags & MSG_NOSIGNAL)
    SIGPIPE_DISABLE

  int result = INLINE_SYSCALL (sendto, 6, fd, buf, n,
    (flags & ~MSG_NOSIGNAL) | MSG_XPG4_2, addr, addr_len);

  if (flags & MSG_NOSIGNAL)
    SIGPIPE_ENABLE

  return result;
}

weak_alias (__sendto, sendto)
LIBC_CANCEL_HANDLED (); /* sys_sendto handles cancellation */
