/* Copyright (C) 2002, 2007, 2008 Free Software Foundation, Inc.
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

#include "pthreadP.h"
#include <string.h>
#include <sys/synch.h>
#include <synch_priv.h>


static const struct pthread_rwlockattr default_attr =
  {
    .lockkind = PTHREAD_RWLOCK_DEFAULT_NP,
    .pshared = PTHREAD_PROCESS_PRIVATE
  };


int
__pthread_rwlock_init (rwlock, attr)
     pthread_rwlock_t *rwlock;
     const pthread_rwlockattr_t *attr;
{
  const struct pthread_rwlockattr *iattr;

  iattr = ((const struct pthread_rwlockattr *) attr) ?: &default_attr;

  memset (rwlock, 0, sizeof(pthread_rwlock_t));
  rwlock->type = iattr->pshared |
      (iattr->lockkind << PTHREAD_RWLOCK_TYPE_SHIFT);
  rwlock->magic = RWL_MAGIC;
  rwlock->mutex.mutex_type = iattr->pshared;
  rwlock->mutex.mutex_flag = LOCK_INITED;
  rwlock->mutex.mutex_magic = MUTEX_MAGIC;
  rwlock->readercv.cond_type = iattr->pshared;
  rwlock->readercv.cond_magic = COND_MAGIC;
  rwlock->writercv.cond_type = iattr->pshared;
  rwlock->writercv.cond_magic = COND_MAGIC;

  return 0;
}
strong_alias (__pthread_rwlock_init, pthread_rwlock_init)
