/* Copyright (C) 2002, 2003, 2004, 2005, 2006, 2007, 2008
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
#include <string.h>
#include <pthreadP.h>
#include <sys/synch.h>
#include <synch_priv.h>

DECLARE_INLINE_SYSCALL (int, lwp_mutex_register, pthread_mutex_t *lp);

static const struct pthread_mutexattr default_attr =
  {
    /* Default is a normal mutex, not shared between processes.  */
    .mutexkind = PTHREAD_MUTEX_NORMAL
  };


int
__pthread_mutex_init (mutex, mutexattr)
     pthread_mutex_t *mutex;
     const pthread_mutexattr_t *mutexattr;
{
  const struct pthread_mutexattr *imutexattr;

  imutexattr = (const struct pthread_mutexattr *) mutexattr ?: &default_attr;

  if (imutexattr->mutexkind & LOCK_ROBUST)
    {
write (2, "MAGIC 1\n", 9);
      if ((mutex->mutex_type & LOCK_INITED))
        return EBUSY;
    }
  else
    {
      memset (mutex, 0, sizeof(pthread_mutex_t));
    }
  mutex->mutex_type = imutexattr->mutexkind;
  mutex->mutex_flag = LOCK_INITED;
  mutex->mutex_magic = MUTEX_MAGIC;
  mutex->mutex_ceiling = imutexattr->ceiling;
  mutex->mutex_cond_waiters = 0;

  /* Register robust shared lock.  */
  if ((imutexattr->mutexkind & (LOCK_ROBUST | LOCK_SHARED)) ==
        (LOCK_ROBUST | LOCK_SHARED))
    {
write (2, "MAGIC 2\n", 9);
      int errval = INLINE_SYSCALL (lwp_mutex_register, 1, mutex);
      if (errval != 0)
        return errval;
    }

  return 0;
}
strong_alias (__pthread_mutex_init, pthread_mutex_init)
INTDEF(__pthread_mutex_init)
