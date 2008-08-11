/* sem_timedwait -- wait on a semaphore.  OpenSolaris version.
   Copyright (C) 2003, 2007, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Paul Mackerras <paulus@au.ibm.com>, 2003.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <errno.h>
#include <sysdep.h>
#include <semaphore.h>

#include <pthreadP.h>
#include <inline-syscall.h>
#include <abstime-to-reltime.h>

DECLARE_INLINE_SYSCALL (int, lwp_sema_timedwait, sem_t *sp,
    struct timespec *tsp, int check_park);


int
sem_timedwait (sem_t *sem, const struct timespec *abstime)
{
  // TODO
  struct timespec _reltime;
  struct timespec *reltime = abstime_to_reltime (abstime, &_reltime);
  if (reltime && reltime->tv_sec < 0)
    {
      __set_errno (ETIMEDOUT);
      return -1;
    }
  int result =  INLINE_SYSCALL (lwp_sema_timedwait, 3, sem, reltime, 1);
  if (result == -1 && errno == ETIME)
    __set_errno (ETIMEDOUT);
  return result;
}
