/* Copyright (C) 2002, 2003, 2005, 2006, 2007, 2008
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

#include <errno.h>
#include <stdlib.h>
#include <pthreadP.h>
#include <inline-syscall.h>

#include <string.h>
#include <sys/synch.h>
#include <synch_priv.h>
#include <assert.h>

DECLARE_INLINE_SYSCALL (int, lwp_mutex_unlock, pthread_mutex_t *lp);

int __mutex_unlock_fast(pthread_mutex_t *mutex);

int
internal_function attribute_hidden
__pthread_mutex_unlock_usercnt (mutex, decr)
     pthread_mutex_t *mutex;
     int decr;
{
  int result = __mutex_unlock_fast (mutex);
  if(result >= 0)
    return result;

#if 0
char buf[200];
sprintf (buf, "%d (%p): pthread_mutex_unlock (pre): mutex_type = %d, mutex_lockbyte = %d, "
    "mutex_waiters = %d, mutex_rcount = %d, mutex_owner = %p, mutex_ownerpid = %d\n",
    pthread_self (), THREAD_SELF, mutex->mutex_type, mutex->mutex_lockbyte, mutex->mutex_waiters,
    mutex->mutex_rcount, (void *)mutex->mutex_owner, mutex->mutex_ownerpid);
write (2, buf, strlen(buf));
#endif

  int errval = INLINE_SYSCALL(lwp_mutex_unlock, 1, mutex);

  /* The kernel does not clear mutex_owner so we clear it here.  */
  if ((mutex->mutex_type & (LOCK_RECURSIVE | LOCK_ERRORCHECK)) && errval == 0)
    {
      mutex->mutex_owner = 0;
      atomic_write_barrier ();
    }

#if 0
sprintf (buf, "%d (%p): pthread_mutex_unlock (post): mutex_type = %d, mutex_lockbyte = %d, "
    "mutex_waiters = %d, mutex_rcount = %d, mutex_owner = %p, mutex_ownerpid = %d, errval = %d\n",
    pthread_self (), THREAD_SELF, mutex->mutex_type, mutex->mutex_lockbyte, mutex->mutex_waiters,
    mutex->mutex_rcount, (void *)mutex->mutex_owner, mutex->mutex_ownerpid, errval);
write (2, buf, strlen(buf));
#endif

  return errval;
}


int
__pthread_mutex_unlock (mutex)
     pthread_mutex_t *mutex;
{
  return __pthread_mutex_unlock_usercnt (mutex, 1);
}
strong_alias (__pthread_mutex_unlock, pthread_mutex_unlock)
strong_alias (__pthread_mutex_unlock, __pthread_mutex_unlock_internal)
weak_alias (__pthread_mutex_unlock, mutex_unlock)
