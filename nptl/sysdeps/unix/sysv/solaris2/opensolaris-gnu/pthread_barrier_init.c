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

#include <errno.h>
#include <pthreadP.h>
#include <string.h>
#include <sys/synch.h>
#include <synch_priv.h>


static const struct pthread_barrierattr default_attr =
  {
    .pshared = PTHREAD_PROCESS_PRIVATE
  };


int
pthread_barrier_init (barrier, attr, count)
     pthread_barrier_t *barrier;
     const pthread_barrierattr_t *attr;
     unsigned int count;
{
  struct pthread_barrier *ibarrier;

  if (__builtin_expect (count == 0, 0))
    return EINVAL;

  const struct pthread_barrierattr *iattr
    = (attr != NULL
       ? iattr = (struct pthread_barrierattr *) attr
       : &default_attr);

  if (iattr->pshared != PTHREAD_PROCESS_PRIVATE
      && __builtin_expect (iattr->pshared != PTHREAD_PROCESS_SHARED, 0))
    /* Invalid attribute.  */
    return EINVAL;

  ibarrier = (struct pthread_barrier *) barrier;

  /* Initialize the individual fields.  */
  memset (&ibarrier->mutex, 0, sizeof(pthread_mutex_t));
  ibarrier->mutex.mutex_type = iattr->pshared;
  ibarrier->mutex.mutex_flag = LOCK_INITED;
  ibarrier->mutex.mutex_magic = MUTEX_MAGIC;
  memset (&ibarrier->cond, 0, sizeof(pthread_cond_t));
  ibarrier->cond.cond_type = iattr->pshared;
  ibarrier->cond.cond_magic = COND_MAGIC;
  ibarrier->left = count;
  ibarrier->init_count = count;
  ibarrier->curr_event = 0;

#if 0
char buf[100];
sprintf(buf, "%d: pthread_barrier_init (%p): FOO 1: %d\n", pthread_self (), ibarrier, ibarrier->left);
write (2, buf, strlen (buf));
#endif
  return 0;
}
