/* Copyright (C) 2002, 2003, 2004, 2006, 2007, 2008
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

#include <tls.h>
#include <ucontext.h>
#include <sys/segments.h>
#include <sys/stack.h>
#include <sys/stack.h>
#include <sys/regset.h>
#include <sys/segments.h>
#include <inline-syscall.h>
#include <sched_priv.h>
#include <createthread_arch.c>

DECLARE_INLINE_SYSCALL (int, lwp_create, ucontext_t *ucp, int flags,
    pthread_t *new_lwp);
DECLARE_INLINE_SYSCALL (int, lwp_continue, pthread_t lwpid);
DECLARE_INLINE_SYSCALL (int, lwp_kill, pthread_t lwpid, int sig);

#ifndef TLS_MULTIPLE_THREADS_IN_TCB
/* Pointer to the corresponding variable in libc.  */
int *__libc_multiple_threads_ptr attribute_hidden;
#endif

static int
create_thread (struct pthread *pd, const struct pthread_attr *attr,
	       STACK_VARIABLES_PARMS)
{
#ifdef TLS_TCB_AT_TP
  assert (pd->header.tcb != NULL);
#endif

  /* Do arch-specific creation.  */
  ucontext_t ctx = {0};
  int errval = create_thread_arch (&ctx, pd, attr, STACK_VARIABLES_ARGS);
  if (errval != 0)
    return errval;

  /* One more thread.  We cannot have the thread do this itself, since it
     might exist but not have been scheduled yet by the time we've returned
     and need to check the value to behave correctly.  We must do it before
     creating the thread, in case it does get scheduled first and then
     might mistakenly think it was the only thread.  In the failure case,
     we momentarily store a false value; this doesn't matter because there
     is no kosher thing a signal handler interrupting us right here can do
     that cares whether the thread count is correct.  */
  atomic_increment (&__nptl_nthreads);

  /* We set the thread to be initially suspended so that we can set
     scheduling magic.  */
  int lwp_flags =
      ((attr->flags & ATTR_FLAG_DAEMON) ? THR_DAEMON : 0) |
      ((attr->flags & ATTR_FLAG_DETACHSTATE) ? THR_DETACHED : 0);
  if (attr->flags & ATTR_FLAG_THR_CREATE == 0)
    lwp_flags |= THR_SUSPENDED;
  errval = INLINE_SYSCALL (lwp_create, 3, &ctx, lwp_flags, &pd->tid);
  if (errval == 0 && (attr->flags & ATTR_FLAG_THR_CREATE) == 0)
    {
      /* Set scheduling.  */
      if (attr->flags & (ATTR_FLAG_SCHED_SET | ATTR_FLAG_POLICY_SET))
        {
          int policy, priority;
          errval = __sched_getscheduler_id (P_LWPID, pd->tid,
            &policy, &priority);
          if (errval == 0)
            {
              if (attr->flags & ATTR_FLAG_SCHED_SET)
                priority = attr->schedparam.__sched_priority;
              if (attr->flags & ATTR_FLAG_POLICY_SET)
                policy = attr->schedpolicy;

              errval = __sched_setscheduler_id (P_LWPID, pd->tid,
                policy, priority);
            }

          if (errval != 0)
            errval = EPERM;
        }

      /* Resume thread if requested.  */
      if (errval == 0)
        {
          if (!(attr->flags & ATTR_FLAG_SUSPENDED))
            errval = INLINE_SYSCALL (lwp_continue, 1, pd->tid);
        }

      /* Kill the thread if we didn't succeed above.  */
      if (errval != 0)
        INLINE_SYSCALL (lwp_kill, 2, pd->tid, SIGKILL);
    }

  if (errval != 0)
    {
      atomic_decrement (&__nptl_nthreads); /* Oops, we lied for a second.  */

      /* Failed.  If the thread is detached, remove the TCB here since
         the caller cannot do this.  The caller remembered the thread
         as detached and cannot reverify that it is not since it must
         not access the thread descriptor again.  */
      if (IS_DETACHED (pd))
        __deallocate_stack (pd);
    }

  return errval;
}
