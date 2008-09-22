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
#include <pthreadP.h>
#include <synch.h>
#include <errno.h>
#include <time.h>
#include <synchP.h>
#include <abstime-to-reltime.h>

DECLARE_INLINE_SYSCALL (int, lwp_mutex_timedlock, mutex_t *lp,
    struct timespec *tsp);

extern int __mutex_lock_fast (mutex_t *mutex, bool try);


int __mutex_timedlock (mutex, abstime)
      mutex_t *mutex;
      const struct timespec *abstime;
{
  /* Handle inconsistent robust mutexes.  */
  if ((mutex->mutex_type & LOCK_ROBUST) &&
      (mutex->mutex_flag & LOCK_NOTRECOVERABLE))
    return ENOTRECOVERABLE;

  /* Always hit the kernel for priority inherit locks.  */
  if ((mutex->mutex_type & LOCK_PRIO_INHERIT) == 0)
    {
      int res = __mutex_lock_fast (mutex, false);
      if(res >= 0)
        return res;
    }
  else
    {
      /* Except when we already hold a recursive lock.  */
      if ((mutex->mutex_type & LOCK_RECURSIVE) && MUTEX_IS_OWNER (mutex))
        {
          /* XXX: Solaris mutexes have no overflow check and don't know about
             EAGAIN; in practice overflow will not occur so we don't care.  */
          if (mutex->mutex_rcount == RECURSION_MAX)
            return EAGAIN;
          ++mutex->mutex_rcount;
          return 0;
        }
    }

  /* Reject invalid timeouts.  */
  if (INVALID_TIMESPEC (abstime))
    return EINVAL;

  struct timespec _reltime;
  struct timespec *reltime = abstime_to_reltime (abstime, &_reltime);
  if (reltime && reltime->tv_sec < 0)
    return ETIME;

  int errval;
  do
    errval = INLINE_SYSCALL (lwp_mutex_timedlock, 2, mutex, reltime);
  while (errval == EINTR);

  /* The kernel sets EDEADLK for priority inherit mutexes.  */
  if (errval == EDEADLK && (mutex->mutex_type & LOCK_PRIO_INHERIT) &&
        (mutex->mutex_type & LOCK_ERRORCHECK) == 0)
    {
      /* We aren't an error checking mutex so we need to block.  */
      INTERNAL_SYSCALL_DECL (err);
      if (abstime)
        {
          int result = INTERNAL_SYSCALL (nanosleep, err, 2, reltime, reltime);
          do
            errval = INTERNAL_SYSCALL_ERRNO (result, err) ? EINTR : ETIMEDOUT;
          while (errval == EINTR);
        }
      else
        {
          do
            INTERNAL_SYSCALL (pause, err, 1, 0);
          while (1);
        }
    }
  if (errval != 0 && errval != EOWNERDEAD)
    return errval;

  /* The kernel does not set mutex_owner so we set it here.  */
  mutex->mutex_owner = THREAD_GETMEM (THREAD_SELF, tid);

  /* The kernel does not set the lockbyte for priority inherit mutexes.  */
  if (mutex->mutex_type & LOCK_PRIO_INHERIT)
    mutex->mutex_lockbyte = 1;

  return errval;
}
