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

#include <time.h>
#include <stddef.h>

static inline struct timespec * abstime_to_reltime (
    const struct timespec *abstime, struct timespec *reltime)
{
  if (!abstime)
    return NULL;

  struct timespec now;
  clock_gettime (CLOCK_REALTIME, &now);
  reltime->tv_sec = abstime->tv_sec - now.tv_sec;
  reltime->tv_nsec = abstime->tv_nsec - now.tv_nsec;
  if (reltime->tv_nsec < 0)
    {
      reltime->tv_nsec += 1000000000;
      --reltime->tv_sec;
    }
  return reltime;
}
