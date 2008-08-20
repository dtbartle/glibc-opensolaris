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

DECLARE_INLINE_SYSCALL (int, connect, int sock, __CONST_SOCKADDR_ARG addr,
    unsigned int addrlen, int version);

int
__libc_connect (fd, addr, len)
     int fd;
     __CONST_SOCKADDR_ARG addr;
     socklen_t len;
{
    return INLINE_SYSCALL (connect, 4, fd, addr, len, SOV_XPG4_2);
}

weak_alias (__libc_connect, __connect)
weak_alias (__libc_connect, connect)
weak_alias (__libc_connect, __connect_internal)
