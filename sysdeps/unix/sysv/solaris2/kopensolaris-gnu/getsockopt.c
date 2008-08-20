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

DECLARE_INLINE_SYSCALL (int, getsockopt, int sock, int level, int option_name,
    void *option_value, socklen_t *option_lenp, int version);

int
getsockopt (fd, level, optname, optval, optlen)
     int fd;
     int level;
     int optname;
     void *optval;
     socklen_t *optlen;
{
  return INLINE_SYSCALL (getsockopt, 6, fd, level, optname,
      optval, optlen, SOV_XPG4_2);
}
