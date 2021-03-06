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

#include <sysdep-cancel.h>
#include <inline-syscall.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

DECLARE_INLINE_SYSCALL (int, sigtimedwait, const sigset_t *set,
    siginfo_t *infop, const struct timespec *timeout);

int
__sigtimedwait_not_cancel (const sigset_t *set, siginfo_t *info,
		const struct timespec *timeout)
{
  if (set == NULL)
    {
      __set_errno(EINVAL);
      return -1;
    }

  /* we don't want people waiting on SIGCANCEL */
  sigset_t tmpset;
  if (set != NULL && __builtin_expect (__sigismember(set, SIGCANCEL), 0))
    {
      memcpy (&tmpset, set, sizeof(sigset_t));
      __sigdelset (&tmpset, SIGCANCEL);
      set = &tmpset;
    }

  return INLINE_SYSCALL (sigtimedwait, 3, set, info, timeout);
}

int
__sigtimedwait (const sigset_t *set, siginfo_t *info,
		const struct timespec *timeout)
{
  if (SINGLE_THREAD_P)
    return __sigtimedwait_not_cancel (set, info, timeout);

  int oldtype = LIBC_CANCEL_ASYNC ();

  int res = __sigtimedwait_not_cancel (set, info, timeout);

  LIBC_CANCEL_RESET (oldtype);

  return res;
}

libc_hidden_def (__sigtimedwait)
weak_alias (__sigtimedwait, sigtimedwait)
