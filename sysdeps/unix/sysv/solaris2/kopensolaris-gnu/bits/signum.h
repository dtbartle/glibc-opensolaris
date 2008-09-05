/* Signal number definitions.  OpenSolaris version.
   Copyright (C) 1994, 1996, 1998, 2008 Free Software Foundation, Inc.
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

#ifdef	_SIGNAL_H

/* Fake signal functions.  */
#define	SIG_ERR	((__sighandler_t) -1) /* Error return.  */
#define	SIG_DFL	((__sighandler_t) 0) /* Default action.  */
#define	SIG_IGN	((__sighandler_t) 1) /* Ignore signal.  */
#ifdef __USE_UNIX98
# define SIG_HOLD ((__sighandler_t) 2) /* Add signal to hold mask.  */
#endif


/* Signals.  */
#define	SIGHUP		1	/* Hangup (POSIX).  */
#define	SIGINT		2	/* Interrupt (ANSI).  */
#define	SIGQUIT		3	/* Quit (POSIX).  */
#define	SIGILL		4	/* Illegal instruction (ANSI).  */
#define	SIGABRT		SIGIOT	/* Abort (ANSI).  */
#define	SIGTRAP		5	/* Trace trap (POSIX).  */
#define	SIGIOT		6	/* IOT trap (4.2 BSD).  */
#define	SIGEMT		7	/* EMT trap (4.2 BSD).  */
#define	SIGFPE		8	/* Floating-point exception (ANSI).  */
#define	SIGKILL		9	/* Kill, unblockable (POSIX).  */
#define	SIGBUS		10	/* Bus error (4.2 BSD).  */
#define	SIGSEGV		11	/* Segmentation violation (ANSI).  */
#define	SIGSYS		12	/* Bad argument to system call (4.2 BSD)*/
#define	SIGPIPE		13	/* Broken pipe (POSIX).  */
#define	SIGALRM		14	/* Alarm clock (POSIX).  */
#define	SIGTERM		15	/* Termination (ANSI).  */
#define	SIGUSR1		16	/* User-defined signal 1 (POSIX).  */
#define	SIGUSR2		17	/* User-defined signal 2 (POSIX).  */
#define	SIGCHLD		18	/* Child status has changed (POSIX).  */
#define	SIGCLD		SIGCHLD	/* Same as SIGCHLD (System V).  */
#define	SIGPWR		19	/* Power failure restart (System V).  */
#define	SIGWINCH	20	/* Window size change (4.3 BSD, Sun).  */
#define	SIGURG		21	/* Urgent condition on socket (4.2 BSD).*/
#define	SIGPOLL		22	/* Pollable event occurred (System V).  */
#define	SIGIO		SIGPOLL	/* I/O now possible (4.2 BSD).  */
#define	SIGSTOP		23	/* Stop, unblockable (POSIX).  */
#define	SIGTSTP		24	/* Keyboard stop (POSIX).  */
#define	SIGCONT		25	/* Continue (POSIX).  */
#define	SIGTTIN		26	/* Background read from tty (POSIX).  */
#define	SIGTTOU		27	/* Background write to tty (POSIX).  */
#define	SIGVTALRM	28	/* Virtual alarm clock (4.2 BSD).  */
#define	SIGPROF		29	/* Profiling alarm clock (4.2 BSD).  */
#define	SIGXCPU		30	/* CPU limit exceeded (4.2 BSD).  */
#define	SIGXFSZ		31	/* File size limit exceeded (4.2 BSD).  */
/* The following signals are new in Solaris 2.  */
#define	SIGWAITING	32	/* Process's lwps are blocked.  */
#define	SIGLWP		33	/* Special signal used by thread library.  */
#define	SIGFREEZE	34	/* Special signal used by CPR.  */
#define	SIGTHAW		35	/* Special signal used by CPR.  */
#define	SIGCANCEL	36	/* Reserved signal for thread cancellation */
#define	SIGLOST		37	/* Resource lost (eg, record-lock lost) */
#define	SIGXRES		38	/* Resource control exceeded */
#define	SIGJVM1		39	/* Reserved signal for Java Virtual Machine */
#define	SIGJVM2		40	/* Reserved signal for Java Virtual Machine */

#define	__SIGRTMIN	41	/* First (highest-priority) realtime signal */
#define	__SIGRTMAX	48	/* Last (lowest-priority) realtime signal */

#define SIGRTMIN	(__libc_current_sigrtmin ())
#define SIGRTMAX	(__libc_current_sigrtmax ())

#endif	/* <signal.h> included.  */

/* descr.h needs _NSIG */
#if defined(_SIGNAL_H) || defined(__need_NSIG)
#undef __need_NSIG
# define _NSIG		49	/* Biggest signal number + 1 */
#endif

/* This is here for lack of a better location.  */
#define SIG2STR_MAX	32
