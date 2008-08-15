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

#include <assert.h>
#include <errno.h>
#include <stdlib.h>
#include <pthreadP.h>
#include <inline-syscall.h>
#include <stdbool.h>

#include <synch_priv.h>
#include <sys/synch.h>

DECLARE_INLINE_SYSCALL (int, lwp_mutex_trylock, pthread_mutex_t *lp);

extern int __mutex_lock_fast(pthread_mutex_t *mutex, bool try);

int
__pthread_mutex_trylock (mutex)
     pthread_mutex_t *mutex;
{
  /* Always hit the kernel for priority inherit locks.  */
  if ((mutex->mutex_type & LOCK_PRIO_INHERIT) == 0)
    {
      int result = __mutex_lock_fast (mutex, true);
      if(result >= 0)
        return result;
    }

  int errval = INLINE_SYSCALL (lwp_mutex_trylock, 1, mutex);

  /* The kernel does not set mutex_owner so we set it here.  */
  if ((mutex->mutex_type & (LOCK_RECURSIVE | LOCK_ERRORCHECK)) && errval == 0)
    {
      mutex->mutex_owner = (uintptr_t)THREAD_SELF;
      atomic_write_barrier ();
    }

  return errval;
}
strong_alias (__pthread_mutex_trylock, pthread_mutex_trylock)
weak_alias (__pthread_mutex_trylock, mutex_trylock)
