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

#include <pthreadP.h>
#include <synch.h>
#include <abstime-to-reltime.h>

DECLARE_INLINE_SYSCALL (int, lwp_sema_timedwait, sema_t *sp,
    struct timespec *tsp, int check_park);


int __sema_timedwait (sem, abstime)
      sema_t *sem;
      struct timespec *abstime;
{
  /* Reject invalid timeouts.  */
/* TODO: if we can acquire the semaphore we should never check abstime */
  if (abstime && (abstime->tv_nsec < 0 || abstime->tv_nsec >= 1000000000))
    return EINVAL;

  struct timespec _reltime;
  struct timespec *reltime = abstime_to_reltime (abstime, &_reltime);
  if (reltime && reltime->tv_sec < 0)
    return ETIME;

  /* Enable asynchronous cancellation.  Required by the standard.  */
  int oldtype = __pthread_enable_asynccancel ();

  int errval = INLINE_SYSCALL (lwp_sema_timedwait, 3, sem, reltime, 1);

  /* Disable asynchronous cancellation.  */
  __pthread_disable_asynccancel (oldtype);

  return errval;
}
