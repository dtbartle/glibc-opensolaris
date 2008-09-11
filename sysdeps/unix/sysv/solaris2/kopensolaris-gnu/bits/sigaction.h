/* The definitions for OpenSolaris's sigaction.
   Copyright (C) 1993-1999, 2000, 2008 Free Software Foundation, Inc.
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

#ifndef _SIGNAL_H
# error "Never include <bits/sigaction.h> directly; use <signal.h> instead."
#endif

#define __need_siginfo_t
#include <bits/siginfo.h>

/* Structure describing the action to be taken when a signal arrives.  */
struct sigaction
{
    int sa_flags;
    union
    {
        void (*_handler)(int);
        void (*_sigaction)(int, siginfo_t *, void *);
    } _funcptr;
#define sa_handler		_funcptr._handler
#define sa_sigaction	_funcptr._sigaction
    sigset_t sa_mask;
#if __WORDSIZE == 32
    int sa_resv[2];
#endif
};

/* Bits in `sa_flags'.  */
#define SA_NOCLDSTOP    0x00020000	/* Don't send SIGCHLD when children stop.  */
#define	SA_NOCLDWAIT	0x00010000	/* Don't send SIGCHLD when children stop.  */
#define SA_SIGINFO		0x00000008	/* Invoke signal-catching function with
                                        three arguments instead of one.  */
#if defined __USE_UNIX98 || defined __USE_MISC
#define SA_ONSTACK		0x00000001	/* Use signal stack by using `sa_restorer'.  */
#define SA_RESTART		0x00000004	/* Restart syscall on signal return.  */
#define SA_NODEFER		0x00000010	/* Don't automatically block the signal when
                                        its handler is being executed.  */
#define SA_RESETHAND	0x00000002
#endif

/* Values for the HOW argument to `sigprocmask'.  */
#define SIG_BLOCK	1	/* Block signals.  */
#define SIG_UNBLOCK	2	/* Unblock signals.  */
#define SIG_SETMASK	3	/* Set the set of blocked signals.  */

#define SIGNO_MASK	0xFF
#define SIGDEFER	0x100
#define SIGHOLD		0x200
#define SIGRELSE	0x400
#define SIGIGNORE	0x800
#define SIGPAUSE	0x1000
