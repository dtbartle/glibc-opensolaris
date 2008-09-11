/* Minimum guaranteed maximum values for system limits.  OpenSolaris version.
   Copyright (C) 1993-1998,2000,2002,2003,2004,2008
    Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* The number of data keys per process.  */
#define _POSIX_THREAD_KEYS_MAX	128
/* This is the value this implementation supports.  */
#define PTHREAD_KEYS_MAX	1024

/* Controlling the iterations of destructors for thread-specific data.  */
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS	4

/* Number of iterations this implementation does.  */
#define PTHREAD_DESTRUCTOR_ITERATIONS	_POSIX_THREAD_DESTRUCTOR_ITERATIONS

/* The number of threads per process.  */
#define _POSIX_THREAD_THREADS_MAX	64

/* Maximum amount by which a process can descrease its asynchronous I/O
   priority level.  */
#define AIO_PRIO_DELTA_MAX	20

/* Minimum size for a thread.  We are free to choose a reasonable value.  */
#define PTHREAD_STACK_MIN	16384

/* Maximum number of POSIX timers available.  */
#define TIMER_MAX	256

/* Maximum number of timer expiration overruns.  */
#define DELAYTIMER_MAX	2147483647

/* Maximum tty name length.  */
#define TTY_NAME_MAX		128
#define TTYNAME_MAX			TTY_NAME_MAX

/* Maximum login name length.  This is arbitrary.  */
#define LOGIN_NAME_MAX		256

/* Maximum host name length.  */
#define HOST_NAME_MAX		64

/* Maximum message queue priority level.  */
#define MQ_PRIO_MAX		32768

/* Maximum number of characters in a path name.  */
#define PATH_MAX    1024

/* Maximum number of files a process can have open.  */
#define OPEN_MAX    256

#define NGROUPS_MAX 16

/* XXX: The 64-bit case is larger but this should be enough for all.  */
#define ARG_MAX    1048320

#define CHILD_MAX   25

#define OPEN_MAX    256

#define SYMLINK_MAX 1024

#define MAX_CANON   256

#define PATH_MAX    1024

#define MAX_INPUT   512

#define PIPE_BUF    5120

/* Maximum message queue priority level.  */
#define MQ_PRIO_MAX		32768

/* Maximum value the semaphore can have.  */
#define SEM_VALUE_MAX   (2147483647)
