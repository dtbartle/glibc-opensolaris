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

#include <sys/types.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <time.h>

/* Solaris only supports user/system time fields of rusage for wait. */

pid_t
__wait4 (__pid_t pid, __WAIT_STATUS stat_loc, int options,
	 struct rusage *usage)
{
  /* start time */
  struct tms start;
  if (usage && times (&start) == (clock_t)-1)
    return -1;

  /* wait */
  pid = __waitpid (pid, stat_loc.__iptr, options);
  if (pid == -1)
    return -1;

  /* end time */
  struct tms end;
  if (usage && times (&end) == (clock_t)-1)
    return -1;

  /* compute deltas */
  if (usage)
    {
      clock_t dutime = end.tms_cutime - start.tms_cutime;
      clock_t dstime = end.tms_cstime - start.tms_cstime;
      usage->ru_utime.tv_sec = dutime / CLOCKS_PER_SEC;
      usage->ru_utime.tv_usec = (dutime % CLOCKS_PER_SEC) * (1000000 / CLOCKS_PER_SEC);
      usage->ru_stime.tv_sec = dstime / CLOCKS_PER_SEC;
      usage->ru_stime.tv_usec = (dstime % CLOCKS_PER_SEC) * (1000000 / CLOCKS_PER_SEC);
    }

  return pid;
}
weak_alias (__wait4, wait4)
