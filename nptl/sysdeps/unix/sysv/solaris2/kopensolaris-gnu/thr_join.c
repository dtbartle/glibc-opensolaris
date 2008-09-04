/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>, 2008.

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
#include <errno.h>
#include <assert.h>
#include <inline-syscall.h>

DECLARE_INLINE_SYSCALL (int, lwp_wait, thread_t lwpid, thread_t *departed);

int thr_join (thread_t thread, thread_t *departed, void **status)
{
  if (thread == 0)
    {
      /* Wait for any thread to terminate.  */
      thread_t _departed;
      int errval = INLINE_SYSCALL (lwp_wait, 2, 0, &_departed);
      if(errval != 0)
        return errval;

      /* Check if this is a thread we know about.  */
      struct pthread *pd = __find_in_stack_list (_departed);
      if (pd == NULL)
        {
          if (departed)
            *departed = _departed;
          if (status)
            *status = 0;
          return 0;
        }

      /* We mark the thread as terminated and as joined.  */
      pd->tid = -1;

      /* Store the return value if the caller is interested.  */
      if (status != NULL)
        *status = pd->result;

      /* Free the TCB.  */
      __free_tcb (pd);

      /* Return the thread_t we waited on if the caller is interested.  */
      if (departed)
        *departed = (thread_t)thread;

      return 0;
    }
  else
    {
      /* Normal wait.  */
      int errval = pthread_join (thread, status);
      if (errval == 0 && departed)
        *departed = thread;
      return errval;
    }
}
