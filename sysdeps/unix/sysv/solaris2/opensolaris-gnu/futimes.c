/* futimes -- change access and modification times of open file.
    OpenSolaris version.
   Copyright (C) 2002,2003,2005,2006,2007,2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

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
#include <sysdep.h>
#include <string.h>
#include <time.h>
#include <utime.h>
#include <sys/time.h>
#include <stdio-common/_itoa.h>
#include <fcntl.h>

/* Change the access time of the file associated with FD to TVP[0] and
   the modification time of FILE to TVP[1].  */
int
__futimes (int fd, const struct timeval tvp[2])
{
  static const char selffd[] = "/proc/self/fd/";
  char fname[sizeof (selffd) + 3 * sizeof (int)];
  fname[sizeof (fname) - 1] = '\0';
  char *cp = _itoa_word ((unsigned int) fd, fname + sizeof (fname) - 1, 10, 0);
  cp = memcpy (cp - sizeof (selffd) + 1, selffd, sizeof (selffd) - 1);

  return utimes (cp, tvp);
}

weak_alias (__futimes, futimes)
