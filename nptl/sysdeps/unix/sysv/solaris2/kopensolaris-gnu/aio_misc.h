/* Copyright (C) 2006, 2007, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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
#include <thread.h>
#include <sys/syscall.h>

/* This has to be relative or we'll end up including nptl's version.  */
#include "../../../../../../sysdeps/pthread/aio_misc.h"

/* We can use cond_timedwait, since it returns EINTR, but it can also return
  ETIME. We get around this by defining a small inline wrapper.  */

static inline int
__aio_pthread_cond_wait (pthread_cond_t *cond, pthread_mutex_t *mutex)
{
  int res = cond_timedwait ((cond_t *)cond, (mutex_t *)mutex, NULL);
  if (res == ETIME)
    return ETIMEDOUT;
  return res;
}

static inline int
__aio_pthread_cond_timedwait (pthread_cond_t *cond, pthread_mutex_t *mutex,
      const struct timespec *abstime)
{
  int res = cond_timedwait ((cond_t *)cond, (mutex_t *)mutex,
      (struct timespec *)abstime);
  if (res == ETIME)
    return ETIMEDOUT;
  return res;
}

#define pthread_cond_wait	__aio_pthread_cond_wait
#define pthread_cond_timedwait	__aio_pthread_cond_timedwait
