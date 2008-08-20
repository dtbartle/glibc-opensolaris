/* Copyright (C) 2002, 2003, 2005, 2008 Free Software Foundation, Inc.
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

#include <sysdep.h>
#include <inline-syscall.h>
#include <signal.h>
#include <unistd.h>
#include <stddef.h>
#include <not-cancel.h>

DECLARE_INLINE_SYSCALL (int64_t, lwp_sigmask, int how, unsigned int bits0,
    unsigned int bits1);


#ifdef _LIBC_REENTRANT
static void cancel_handler (void *arg);

# define CLEANUP_HANDLER \
  __libc_cleanup_region_start (1, cancel_handler, &pid)

# define CLEANUP_RESET \
  __libc_cleanup_region_end (0)

#define FORK() __fork_block_signals (&pid)

static inline pid_t __fork_block_signals (pid_t *pid)
{
  /* Block all signals. */
  rval_t oldmask;
  oldmask.rval64 = INLINE_SYSCALL (lwp_sigmask, 3, SIG_SETMASK,
      (unsigned int)-1, (unsigned int)-1);

  *pid = fork ();

  /* Restore signals.  */
  (void)INLINE_SYSCALL (lwp_sigmask, 3, SIG_SETMASK,
      (unsigned int)oldmask.rval1, (unsigned int)oldmask.rval2);

  return *pid;
}
#endif

#include <sysdeps/posix/system.c>

#ifdef _LIBC_REENTRANT
/* The cancellation handler.  */
static void
cancel_handler (void *arg)
{
  pid_t child = *(pid_t *) arg;

  __kill (child, SIGKILL);

  TEMP_FAILURE_RETRY (__waitpid (child, NULL, 0));

  DO_LOCK ();

  if (SUB_REF () == 0)
    {
      (void) __sigaction (SIGQUIT, &quit, (struct sigaction *) NULL);
      (void) __sigaction (SIGINT, &intr, (struct sigaction *) NULL);
    }

  DO_UNLOCK ();
}
#endif
