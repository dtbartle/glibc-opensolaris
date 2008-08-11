/* Copyright (C) 2002,2003,2004,2005,2006,2007,2008
    Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.
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

#include <assert.h>
#include <errno.h>
#include <time.h>
#include <pthreadP.h>
#include <not-cancel.h>
#include <inline-syscall.h>
#include <stdbool.h>
#include <abstime-to-reltime.h>
#include <stdio.h>

#include <unistd.h>
#include <string.h>
#include <sys/synch.h>
#include <synch_priv.h>

DECLARE_INLINE_SYSCALL (int, lwp_mutex_timedlock, pthread_mutex_t *lp,
    struct timespec *tsp);

extern int __mutex_lock_fast(pthread_mutex_t *mutex, bool try);

int
pthread_mutex_timedlock (mutex, abstime)
     pthread_mutex_t *mutex;
     const struct timespec *abstime;
{
  /* Reject invalid timeouts.  */
  if (abstime && (abstime->tv_nsec < 0 || abstime->tv_nsec >= 1000000000))
    return EINVAL;

  int result = __mutex_lock_fast (mutex, false);
  if(result >= 0)
    return result;

  struct timespec _reltime;
  struct timespec *reltime = abstime_to_reltime (abstime, &_reltime);
  if (reltime && reltime->tv_sec < 0)
    {
      __set_errno (ETIMEDOUT);
      return -1;
    }

#if 0
char buf[200];
sprintf (buf, "%d (%p): pthread_mutex_timedlock (pre): mutex_type = %d, mutex_lockbyte = %d, "
    "mutex_waiters = %d, mutex_rcount = %d, mutex_owner = %p, mutex_ownerpid = %d\n",
    pthread_self (), THREAD_SELF, mutex->mutex_type, mutex->mutex_lockbyte, mutex->mutex_waiters,
    mutex->mutex_rcount, (void *)mutex->mutex_owner, mutex->mutex_ownerpid);
write (2, buf, strlen(buf));
#endif

  int errval = INLINE_SYSCALL (lwp_mutex_timedlock, 2, mutex, reltime);

  if (errval == ETIME)
    errval = ETIMEDOUT;

  /* The kernel does not set mutex_owner so we set it here.  */
  if ((mutex->mutex_type & (LOCK_RECURSIVE | LOCK_ERRORCHECK)) && errval == 0)
    {
      mutex->mutex_owner = (uintptr_t)THREAD_SELF;
      atomic_write_barrier ();
    }

#if 0
sprintf (buf, "%d (%p): pthread_mutex_timedlock (post): mutex_type = %d, mutex_lockbyte = %d, "
    "mutex_waiters = %d, mutex_rcount = %d, mutex_owner = %p, mutex_ownerpid = %d, errval = %d\n",
    pthread_self (), THREAD_SELF, mutex->mutex_type, mutex->mutex_lockbyte, mutex->mutex_waiters,
    mutex->mutex_rcount, (void *)mutex->mutex_owner, mutex->mutex_ownerpid, errval);
write (2, buf, strlen(buf));
#endif

  return errval;
}
