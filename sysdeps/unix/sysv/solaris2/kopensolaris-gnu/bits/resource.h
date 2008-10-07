/* Bit values & structures for resource limits.  OpenSolaris version.
   Copyright (C) 1994, 1996, 1997, 1998, 1999, 2000, 2004, 2005, 2008
   Free Software Foundation, Inc.
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

#ifndef _SYS_RESOURCE_H
# error "Never use <bits/resource.h> directly; include <sys/resource.h> instead."
#endif

#include <bits/types.h>

/* Transmute defines to enumerations.  The macro re-definitions are
   necessary because some programs want to test for operating system
   features with #ifdef RUSAGE_SELF.  In ISO C the reflexive
   definition is a no-op.  */

/* Kinds of resource limit.  */
enum __rlimit_resource
{
  /* Per-process CPU limit, in seconds.  */
  RLIMIT_CPU = 0,
#define RLIMIT_CPU RLIMIT_CPU

  /* Largest file that can be created, in bytes.  */
  RLIMIT_FSIZE = 1,
#define	RLIMIT_FSIZE RLIMIT_FSIZE

  /* Maximum size of data segment, in bytes.  */
  RLIMIT_DATA = 2,
#define	RLIMIT_DATA RLIMIT_DATA

  /* Maximum size of stack segment, in bytes.  */
  RLIMIT_STACK = 3,
#define	RLIMIT_STACK RLIMIT_STACK

  /* Largest core file that can be created, in bytes.  */
  RLIMIT_CORE = 4,
#define	RLIMIT_CORE RLIMIT_CORE

  /* Number of open files.  */
  RLIMIT_NOFILE = 5,
#define RLIMIT_NOFILE RLIMIT_NOFILE

  /* Maximum mapped memory.  */
  RLIMIT_AS = 6,
#define RLIMIT_AS RLIMIT_AS
#define RLIMIT_VMEM RLIMIT_AS

  __RLIMIT_NLIMITS = 7,
  __RLIM_NLIMITS = __RLIMIT_NLIMITS
#define RLIMIT_NLIMITS __RLIMIT_NLIMITS
#define RLIM_NLIMITS __RLIM_NLIMITS
};

/* Type for resource quantity measurement.  */
#ifndef __USE_FILE_OFFSET64
typedef __rlim_t rlim_t;
#else
typedef __rlim64_t rlim_t;
#endif
#ifdef _SYSCALL32
typedef __uint32_t rlim32_t;
#endif
#ifdef __USE_LARGEFILE64
typedef __rlim64_t rlim64_t;
#endif

/* Value to indicate that there is no limit.  */
#ifdef __USE_LARGEFILE64
# define RLIM64_INFINITY	((rlim64_t)-3)
# define RLIM64_SAVED_MAX	((rlim64_t)-2)
# define RLIM64_SAVED_CUR	((rlim64_t)-1)
#endif
#if __WORDSIZE == 64
# define RLIM_INFINITY		((rlim_t)-3l)
# define RLIM_SAVED_MAX		((rlim_t)-2l)
# define RLIM_SAVED_CUR		((rlim_t)-1l)
#else
# define RLIM_INFINITY		0x7FFFFFFF
# define RLIM_SAVED_MAX		0x7FFFFFFE
# define RLIM_SAVED_CUR		0x7FFFFFFD
#endif
#ifdef _SYSCALL32
# define RLIM32_INFINITY	0x7FFFFFFF
# define RLIM32_SAVED_MAX	0x7FFFFFFE
# define RLIM32_SAVED_CUR	0x7FFFFFFD
#endif

#if __WORDSIZE == 64
# define RLIM_SAVED(x)	1
# define RLIM_NSAVED	RLIM_NLIMITS
#else
# define RLIM_SAVED(x)	(x <= RLIMIT_FSIZE)
# define RLIM_NSAVED	(RLIMIT_FSIZE + 1)
#endif

struct rlimit
  {
    /* The current (soft) limit.  */
    rlim_t rlim_cur;
    /* The hard limit.  */
    rlim_t rlim_max;
  };

#ifdef _SYSCALL32
struct rlimit32
  {
	rlim32_t rlim_cur;
	rlim32_t rlim_max;
};
#endif

#ifdef __USE_LARGEFILE64
struct rlimit64
  {
    /* The current (soft) limit.  */
    rlim64_t rlim_cur;
    /* The hard limit.  */
    rlim64_t rlim_max;
 };
#endif

/* Whose usage statistics do you want?  */
enum __rusage_who
{
  /* The calling process.  */
  RUSAGE_SELF = 0,
#define RUSAGE_SELF RUSAGE_SELF

  /* The lwp.  */
  RUSAGE_LWP = 1,
#define RUSAGE_LWP RUSAGE_LWP

  /* All of its terminated child processes.  */
  RUSAGE_CHILDREN = 2
#define RUSAGE_CHILDREN RUSAGE_CHILDREN
};

#define __need_timeval
#define __need_itimerval
#include <bits/time.h>		/* For `struct timeval'.  */

/* Structure which says how much of each resource has been used.  */
struct rusage
  {
    /* Total amount of user time used.  */
    struct timeval ru_utime;
    /* Total amount of system time used.  */
    struct timeval ru_stime;
    /* Maximum resident set size (in kilobytes).  */
    long int ru_maxrss;
    /* Amount of sharing of text segment memory
       with other processes (kilobyte-seconds).  */
    long int ru_ixrss;
    /* Amount of data segment memory used (kilobyte-seconds).  */
    long int ru_idrss;
    /* Amount of stack memory used (kilobyte-seconds).  */
    long int ru_isrss;
    /* Number of soft page faults (i.e. those serviced by reclaiming
       a page from the list of pages awaiting reallocation.  */
    long int ru_minflt;
    /* Number of hard page faults (i.e. those that required I/O).  */
    long int ru_majflt;
    /* Number of times a process was swapped out of physical memory.  */
    long int ru_nswap;
    /* Number of input operations via the file system.  Note: This
       and `ru_oublock' do not include operations with the cache.  */
    long int ru_inblock;
    /* Number of output operations via the file system.  */
    long int ru_oublock;
    /* Number of IPC messages sent.  */
    long int ru_msgsnd;
    /* Number of IPC messages received.  */
    long int ru_msgrcv;
    /* Number of signals delivered.  */
    long int ru_nsignals;
    /* Number of voluntary context switches, i.e. because the process
       gave up the process before it had to (usually to wait for some
       resource to be available).  */
    long int ru_nvcsw;
    /* Number of involuntary context switches, i.e. a higher priority process
       became runnable or the current process used up its time slice.  */
    long int ru_nivcsw;
  };

/* The type of the WHICH argument to `getpriority' and `setpriority',
   indicating what flavor of entity the WHO argument specifies.  */
enum __priority_which
{
  PRIO_PROCESS = 0,		/* WHO is a process ID.  */
#define PRIO_PROCESS PRIO_PROCESS
  PRIO_PGRP = 1,		/* WHO is a process group ID.  */
#define PRIO_PGRP PRIO_PGRP
  PRIO_USER = 2,			/* WHO is a user ID.  */
#define PRIO_USER PRIO_USER
  PRIO_GROUP = 3,
#define PRIO_GROUP PRIO_GROUP
  PRIO_SESSION = 4,
#define PRIO_SESSION PRIO_SESSION
  PRIO_LWP = 5,
#define PRIO_LWP PRIO_LWP
  PRIO_TASK = 6,
#define PRIO_TASK PRIO_TASK
  PRIO_PROJECT = 7,
#define PRIO_PROJECT PRIO_PROJECT
  PRIO_ZONE = 8,
#define PRIO_ZONE PRIO_ZONE
  PRIO_CONTRACT = 9,
#define PRIO_CONTRACT PRIO_CONTRACT
};

enum
{
	_RUSAGESYS_GETRUSAGE = 0,
#define _RUSAGESYS_GETRUSAGE	_RUSAGESYS_GETRUSAGE
	_RUSAGESYS_GETRUSAGE_CHLD = 1,
#define _RUSAGESYS_GETRUSAGE_CHLD	_RUSAGESYS_GETRUSAGE_CHLD
	_RUSAGESYS_GETRUSAGE_LWP = 2,
#define _RUSAGESYS_GETRUSAGE_LWP	_RUSAGESYS_GETRUSAGE_LWP
	_RUSAGESYS_GETVMUSAGE = 3
#define _RUSAGESYS_GETVMUSAGE	_RUSAGESYS_GETVMUSAGE
};

#define PRIO_MIN	-20
#define PRIO_MAX	20
