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

#include <stdlib.h>
#include <unistd.h>

/* TODO: This should go away once we put fdwalk in stdlib.h.  */
extern int fdwalk(int (*)(void *, int), void *);

static int close_lowfd (void *lowfdp, int fd)
{
  int lowfd = (int)lowfdp;
  if (fd >= lowfd)
    close (fd);
  return 0;
}

void closefrom (int lowfd)
{
  fdwalk (close_lowfd, (void *)lowfd);
}