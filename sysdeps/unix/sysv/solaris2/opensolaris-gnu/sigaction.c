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

#include <inline-syscall.h>
#include <errno.h>
#include <stddef.h>
#include <signal.h>
#include <string.h>
#include <ucontext.h>
#include <tls.h>
#include <assert.h>
#include <bits/libc-lock.h>
#include <stdio.h>

static void (*sighandlers[_NSIG])(int, struct siginfo *, void *) = {0};
__libc_lock_define_initialized (, signal_lock);

/* Solaris expects the ucontext_t to be switched back at the end
  of signal processing; one cannot simply return from the
  sighandler. As well, Solaris always calls the 3-param version
  of the handler (i.e. sa_sigaction).  */

/* Defined in sighandler.c.  */
extern void __sighandler(int, siginfo_t *, void *);

DECLARE_INLINE_SYSCALL (int, sigaction, int signum,
    const struct sigaction *act, struct sigaction *oldact);

int
__libc_sigaction (sig, act, oact)
     int sig;
     const struct sigaction *act;
     struct sigaction *oact;
{
  int result;

  if (sig < 0 || sig >= NSIG)
    {
      __set_errno (EINVAL);
      return -1;
    }

  if (!act && !oact)
    {
      __set_errno (EINVAL);
      return -1;
    }

  /* Block all signals and lock. */
  sigset_t fillset, oldset;
  if (sigfillset (&fillset) != 0)
    return -1;
  if (sigprocmask (SIG_SETMASK, &fillset, &oldset) != 0)
    return -1;
  __libc_lock_lock (signal_lock);

  void (*old_sigaction)(int, siginfo_t *, void *) = sighandlers[sig];
  if (act)
    {
      struct sigaction _act = *act;
      if (act->sa_handler != SIG_DFL && act->sa_handler != SIG_IGN)
        {
          _act.sa_sigaction = __sighandler;
        }
      result = INLINE_SYSCALL (sigaction, 3, sig, &_act, oact);
      if(result != -1)
        {
          sighandlers[sig] = act->sa_sigaction;
        }
    }

  if (oact)
    {
      /* If we called sigaction above don't call it again.  */
      if (!act)
        result = INLINE_SYSCALL(sigaction, 3, sig, NULL, oact);
      if (result != -1)
        {
          if (oact->sa_handler != SIG_DFL && oact->sa_handler != SIG_IGN)
            {
              oact->sa_sigaction = old_sigaction;
            }
        }
    }

  /* Unlock and restore signals.  */
  __libc_lock_unlock (signal_lock);
  assert (sigprocmask (SIG_SETMASK, &oldset, NULL) == 0);

  return result;
}

libc_hidden_def (__libc_sigaction)
#ifndef LIBC_SIGACTION
weak_alias (__libc_sigaction, __sigaction)
libc_hidden_weak (__sigaction)
weak_alias (__libc_sigaction, sigaction)
#endif


void __sighandler (int sig, siginfo_t *sip, void *uvp)
{
  assert (sig >= 0 && sig < NSIG);

  /* Block all signals and lock.  */
  sigset_t fillset, oldset;
  if (sigfillset (&fillset) != 0)
    return;
  if (sigprocmask (SIG_SETMASK, &fillset, &oldset) != 0)
    return;
  __libc_lock_lock (signal_lock);

  void (*handler)(int, siginfo_t *, void *) = sighandlers[sig];
  ucontext_t *uctx = (ucontext_t*)uvp;

  /* Unlock and restore signals.  */
  __libc_lock_unlock (signal_lock);
  assert (sigprocmask (SIG_SETMASK, &oldset, NULL) == 0);

  (*handler)(sig, sip, uvp);

  setcontext (uctx);
  assert (0); /* never reached */
}
