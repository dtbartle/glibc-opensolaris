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
#include <stdio.h>


int
pthread_barrier_destroy (barrier)
     pthread_barrier_t *barrier;
{
  struct pthread_barrier *ibarrier = (struct pthread_barrier *) barrier;

  int errval = __pthread_mutex_lock (&ibarrier->mutex);
  if (errval != 0)
    return EINVAL;

  /* Make sure barrier is not exiting.  */
  while (errval == 0 && (ibarrier->flag & BARRIER_EXITING))
    {
      errval = __cond_reltimedwait_internal ((cond_t *)&ibarrier->cond,
          (mutex_t *)&ibarrier->mutex, NULL, 0);
      if (errval == EINTR)
        errval = 0;
    }

  if (__builtin_expect (ibarrier->left != ibarrier->init_count, 0))
    errval = EBUSY;

  (void)__pthread_mutex_unlock (&ibarrier->mutex);
  return errval;
}
