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

#include <not-cancel.h>
#include <fcntl.h>
#include <unistd.h>

/* F_DUPFD expects the target fd to be closed before calling it; if
  we close first we create a race condition where the fd could be
  reused before we call fcntl. Solaris solves this by providing
  F_DUP2FD, which is atomic in this regard. */

int
__dup2 (fd, fd2)
     int fd;
     int fd2;
{
  return fcntl_not_cancel (fd, F_DUP2FD, fd2);
}

libc_hidden_def (__dup2)
weak_alias (__dup2, dup2)
