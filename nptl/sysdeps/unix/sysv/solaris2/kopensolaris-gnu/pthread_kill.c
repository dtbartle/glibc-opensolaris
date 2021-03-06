/* Copyright (C) 2002, 2003, 2004, 2006, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.

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
#include <signal.h>
#include <pthreadP.h>
#include <tls.h>
#include <sysdep.h>
#include <kernel-features.h>


int
__pthread_kill (threadid, signo)
     pthread_t threadid;
     int signo;
{
#ifndef PTHREAD_T_IS_TID
  struct pthread *pd = (struct pthread *) threadid;
#else
  struct pthread *pd = __find_in_stack_list (threadid);
#endif

  /* Make sure the descriptor is valid.  */
  if (INVALID_TD_P (pd))
    /* Not a valid thread handle.  */
    return ESRCH;

  /* Disallow sending the signal we use for cancellation, timers, for
     for the setxid implementation.  */
  if (signo == SIGCANCEL || signo == SIGTIMER)
    return EINVAL;

  /* We have a special syscall to do the work.  */
  INTERNAL_SYSCALL_DECL (err);
  int val = INTERNAL_SYSCALL (tkill, err, 2, threadid, signo);

  return (INTERNAL_SYSCALL_ERROR_P (val, err)
	  ? INTERNAL_SYSCALL_ERRNO (val, err) : 0);
}
strong_alias (__pthread_kill, pthread_kill)
weak_alias (__pthread_kill, _lwp_kill)
weak_alias (__pthread_kill, thr_kill)
