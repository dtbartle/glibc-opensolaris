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

/* Get the arch-specific version.  */
#include_next <pthreaddef.h>

/* Register atfork handlers to protect signal_lock.  */
extern void sigaction_atfork (void);

/* We need to tell the kernel about the allocated stack.  */
#define PLATFORM_THREAD_START                   \
    {                                           \
      pd->stack.ss_sp = pd->stackblock;         \
      pd->stack.ss_sp = pd->stackblock_size;    \
      pd->stack.ss_flags = 0;                   \
      setustack (&pd->stack);                   \
    }

#ifndef __stack_t_defined
# define __need_stack_t
# include <bits/sigstack.h>
#endif

#define PLATFORM_PTHREAD_INIT                       \
    sigaction_atfork ();                            \
    THREAD_SETMEM (pd, main_thread, 1);             \
    stack_t *_stack;                                \
	if (getustack (&_stack) == 0 && _stack)         \
      {                                             \
        pd->stackblock = _stack->ss_sp;             \
        pd->stackblock_size = _stack->ss_size;      \
      }                                             \
    PLATFORM_THREAD_START

/* Additional descr fields.  */
# define PLATFORM_DESCR_FIELDS  \
    int main_thread;            \
    stack_t stack;

/* stackblock/stackblock_size should always be filled.  */
#define GET_MAIN_STACK_INFO(stackaddr, stacksize)	ENOSYS

/* Use tid as pthread_t (instead of descr).  */
#define PTHREAD_T_IS_TID

/* Use pthread scheduler functions in tpp.  */
#define TPP_PTHREAD_SCHED

/* pthread_ is unsigned.  */
#define FREE_P(descr) ((descr)->tid == (pthread_t)-1)

/* The first thread has a large (10M) stack so use the arch defaults.  */
#define PTHREAD_USE_ARCH_STACK_DEFAULT_SIZE

/* It is known that the first lwpid is 1.  */
#define FIRST_THREAD_TID	1

/* We need to be passed the stacksize.  */
#define NEED_STACK_SIZE

/* __exit_thread_inline is the same for all architectures.  */
#include <inline-syscall.h>

DECLARE_INLINE_SYSCALL (void, lwp_exit, void);

#undef __exit_thread_inline
#define __exit_thread_inline(val) \
    INLINE_SYSCALL (lwp_exit, 0);
