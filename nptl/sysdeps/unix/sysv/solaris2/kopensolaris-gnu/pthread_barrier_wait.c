/* Copyright (C) 2003, 2004, 2007, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Martin Schwidefsky <schwidefsky@de.ibm.com>, 2003.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

#include <errno.h>
#include <pthreadP.h>
#include <stdio.h>
#include <not-cancel.h>


/* Wait on barrier.  */
int
pthread_barrier_wait (barrier)
     pthread_barrier_t *barrier;
{
  struct pthread_barrier *ibarrier = (struct pthread_barrier *) barrier;

  int errval = pthread_mutex_lock (&ibarrier->mutex);
  if (errval != 0)
    return errval;

  /* Make sure barrier is not exiting.  */
  while (ibarrier->flag & BARRIER_EXITING)
    {
      errval = __cond_reltimedwait_internal ((cond_t *)&ibarrier->cond,
        (mutex_t *)&ibarrier->mutex, NULL, 0);
      if (errval != EINTR && errval != 0)
        {
          (void)pthread_mutex_unlock (&ibarrier->mutex);
          return errval;
        }
    }

  /* A thread entered the barrier.  */
  --ibarrier->left;

  if (ibarrier->left == 0)
    {
      /* Increment the event counter to avoid invalid wake-ups and tell the
         current waiters that it is their turn. Also reset the barrier.  */
      ++ibarrier->curr_event;

      ibarrier->flag |= BARRIER_EXITING;

      /* Wake other threads.  */
      (void)pthread_cond_broadcast (&ibarrier->cond);
      errval = PTHREAD_BARRIER_SERIAL_THREAD;
    }
  else
    {
      /* Wait until the current barrier event is done.  */
      int curr_event = ibarrier->curr_event;
      do
        {
          errval = __cond_reltimedwait_internal ((cond_t *)&ibarrier->cond,
              (mutex_t *)&ibarrier->mutex, NULL, 0);
          if (errval != EINTR && errval != 0)
            {
              (void)pthread_mutex_unlock (&ibarrier->mutex);
              return errval;
            }
        }
      while (curr_event == ibarrier->curr_event);
    }

  /* If we are the last thread notify barrier waiters.  */
  if (++ibarrier->left == ibarrier->init_count)
    {
      ibarrier->flag &= ~BARRIER_EXITING;
      (void)pthread_cond_broadcast (&ibarrier->cond);
    }

  (void)pthread_mutex_unlock (&ibarrier->mutex);
  return errval;
}
