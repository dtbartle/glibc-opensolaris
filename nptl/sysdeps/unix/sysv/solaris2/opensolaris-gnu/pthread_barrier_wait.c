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
#include <stdbool.h>


/* Wait on barrier.  */
int
pthread_barrier_wait (barrier)
     pthread_barrier_t *barrier;
{
  bool serial_thread = false;

  struct pthread_barrier *ibarrier = (struct pthread_barrier *) barrier;

  int errval = pthread_mutex_lock (&ibarrier->mutex);
  if (errval != 0)
    return errval;

  /* A thread entered the barrier.  */
  --ibarrier->left;
#if 0
char buf[100];
sprintf(buf, "%d: pthread_barrier_wait (%p): FOO 1: %d\n", pthread_self (), ibarrier, ibarrier->left);
write (2, buf, strlen (buf));
#endif

  if (ibarrier->left == 0)
    {
      /* Increment the event counter to avoid invalid wake-ups and tell the
         current waiters that it is their turn. Also reset the barrier.  */
      ++ibarrier->curr_event;
      ibarrier->left = ibarrier->init_count;
      atomic_write_barrier ();

      errval = pthread_mutex_unlock (&ibarrier->mutex);
      if (errval != 0)
        return errval;

      /* Wake other threads.  */
      errval = pthread_cond_broadcast (&ibarrier->cond);
      if (errval != 0)
        return errval;

      return PTHREAD_BARRIER_SERIAL_THREAD;
    }

  atomic_write_barrier ();

  /* Wait until the current barrier event is done.  */
  int curr_event = ibarrier->curr_event;
  do
    {
// TODO: not_cancel
      errval = pthread_cond_wait (&ibarrier->cond, &ibarrier->mutex);
      if (errval != 0)
        return errval;
    }
  while (curr_event == ibarrier->curr_event);

  return pthread_mutex_unlock (&ibarrier->mutex);
}
