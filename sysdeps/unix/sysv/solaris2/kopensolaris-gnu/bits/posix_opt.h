/* Define POSIX options for OpenSolaris.
   Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _POSIX_OPT_H
#define _POSIX_OPT_H

#define _POSIX_ASYNCHRONOUS_IO	200112L
#define _POSIX_FSYNC	200112L
#define _POSIX_MAPPED_FILES	200112L
#define _POSIX_MEMLOCK	200112L
#define _POSIX_MEMLOCK_RANGE	200112L
#define _POSIX_MEMORY_PROTECTION	200112L
#define _POSIX_MESSAGE_PASSING	200112L
#define _POSIX_PRIORITY_SCHEDULING	200112L
#define _POSIX_REALTIME_SIGNALS	200112L
#define _POSIX_SEMAPHORES	200112L
#define _POSIX_SHARED_MEMORY_OBJECTS	200112L
#define _POSIX_SYNCHRONIZED_IO	200112L

#define _POSIX_THREAD_SAFE_FUNCTIONS	200112L
#define _POSIX_THREADS	200112L
#define _POSIX_THREAD_ATTR_STACKADDR	200112L
#define _POSIX_THREAD_ATTR_STACKSIZE	200112L
#define _POSIX_THREAD_PROCESS_SHARED	200112L
#define _POSIX_THREAD_PRIORITY_SCHEDULING	200112L
#define _POSIX_TIMERS	200112L

#define _POSIX_BARRIERS	200112L
#define _POSIX_CLOCK_SELECTION	200112L
#define _POSIX_IPV6	200112L
#define _POSIX_MONOTONIC_CLOCK	200112L
#define _POSIX_RAW_SOCKETS	200112L
#define _POSIX_READER_WRITER_LOCKS	200112L
#define _POSIX_SPAWN	200112L
#define _POSIX_SPIN_LOCKS	200112L
#define _POSIX_TIMEOUTS	200112L
#define _POSIX2_CHAR_TERM	200112L

#define _POSIX_THREAD_PRIO_INHERIT	200112L
#define _POSIX_THREAD_PRIO_PROTECT	200112L

#define _LFS_LARGEFILE	1
#define _LFS64_LARGEFILE	1
#define _LFS64_STDIO	11
#define _LFS64_ASYNCHRONOUS_IO	1

#define _POSIX_REGEXP	1
#define _POSIX_SAVED_IDS	1
#define _POSIX_SHELL	1
#define _POSIX_JOB_CONTROL	1

#define _POSIX_CPUTIME	-1
#define _POSIX_ADVISORY_INFO	-1
#define _POSIX_PRIORITIZED_IO	-1
#define _POSIX_SPORADIC_SERVER	-1
#define _POSIX_THREAD_CPUTIME	-1
#define _POSIX_THREAD_SPORADIC_SERVER	-1
#define _POSIX_TRACE	-1
#define _POSIX_TRACE_EVENT_FILTER	-1
#define _POSIX_TRACE_INHERIT	-1
#define _POSIX_TRACE_LOG	-1
#define _POSIX_TYPED_MEMORY_OBJECTS	-1

#define _POSIX_VDISABLE	'\0'

#endif /* _BITS_POSIX_OPT_H */
