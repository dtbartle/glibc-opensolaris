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

  ucontext_t ctx = {0};

  /* Clone the segment registers (except gs - see below).  */
  ucontext_t _ctx;
  _ctx.uc_flags = UC_CPU;
  if (getcontext(&_ctx) != 0)
    return errno;
  ctx.uc_mcontext.gregs[CS] = _ctx.uc_mcontext.gregs[CS];
  ctx.uc_mcontext.gregs[DS] = _ctx.uc_mcontext.gregs[DS];
  ctx.uc_mcontext.gregs[ES] = _ctx.uc_mcontext.gregs[ES];
  ctx.uc_mcontext.gregs[FS] = _ctx.uc_mcontext.gregs[FS];
  ctx.uc_mcontext.gregs[SS] = _ctx.uc_mcontext.gregs[SS];

  /* Setup the stack (note that it grows down).  */
  uint32_t *stack_ptr = (uint32_t *)((uintptr_t)((uint32_t *)stackaddr - 1) &
    ~(STACK_ALIGN - 1)) + 1;
  *--stack_ptr = (uint32_t)pd; /* arg 1 */
  *--stack_ptr = 0; /* return addr (thread_start never returns) */
  ctx.uc_mcontext.gregs[UESP] = (greg_t)stack_ptr;
  ctx.uc_mcontext.gregs[EBP] = (greg_t)(stack_ptr + 2); // TODO
  ctx.uc_mcontext.gregs[EIP] = (greg_t)start_thread;
  ctx.uc_flags |= UC_CPU;

  /* This is a hack to get the kernel to set gs for us.  */
  ctx.uc_mcontext.gregs[GS] = (greg_t)LWPGS_SEL;
  ctx.uc_mcontext.gregs[ESP] = (greg_t)pd;

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
  int lwp_flags = THR_SUSPENDED |
      ((attr->flags & ATTR_FLAG_DAEMON) ? THR_DAEMON : 0) |
      ((attr->flags & ATTR_FLAG_DETACHSTATE) ? THR_DETACHED : 0);
  int errval = INLINE_SYSCALL (lwp_create, 3, &ctx, lwp_flags, &pd->tid);
  if (errval == 0)
    {
      // TODO: set scheduling

      if (errval == 0)
        {
          /* Resume thread if requested.  */
          if (!(attr->flags & ATTR_FLAG_SUSPENDED))
            {
              errval = INLINE_SYSCALL (lwp_continue, 1, pd->tid);
            }
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
