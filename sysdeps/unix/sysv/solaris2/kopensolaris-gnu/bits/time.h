/* System-dependent timing definitions.  OpenSolaris version.
   Copyright (C) 1996,1997,1999-2002,2003,2008 Free Software Foundation, Inc.
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

/*
 * Never include this file directly; use <time.h> instead.
 */

#ifndef __need_timeval
# ifndef _BITS_TIME_H
#  define _BITS_TIME_H	1

/* ISO/IEC 9899:1990 7.12.1: <time.h>
   The macro `CLOCKS_PER_SEC' is the number per second of the value
   returned by the `clock' function. */
/* CAE XSH, Issue 4, Version 2: <time.h>
   The value of CLOCKS_PER_SEC is required to be 1 million on all
   XSI-conformant systems. */
#  define CLOCKS_PER_SEC  1000000l

#  if !defined __STRICT_ANSI__ && !defined __USE_XOPEN2K
/* Even though CLOCKS_PER_SEC has such a strange value CLK_TCK
   presents the real value for clock ticks per second for the system.  */
#   include <bits/types.h>
extern long int __sysconf (int);
#   define CLK_TCK ((__clock_t) __sysconf (2))	/* 2 is _SC_CLK_TCK */
#  endif

#  ifdef __USE_POSIX199309

/* Thread-specific userland-only CPU-time clock.  */
#   define CLOCK_VIRTUAL		1
/* Thread-specific CPU-time clock.  */
#   define CLOCK_THREAD_CPUTIME_ID	2
/* Identifier for system-wide realtime clock.  */
#   define CLOCK_REALTIME		3
/* Monotonic system-wide clock.  */
#   define CLOCK_MONOTONIC		4
/* High-resolution timer from the CPU.  */
#   define CLOCK_PROCESS_CPUTIME_ID	5
/* OpenSolaris defines these.  */
#   define __CLOCK_REALTIME0	0
#   define CLOCK_HIGHRES	CLOCK_MONOTONIC
#   define CLOCK_PROF		CLOCK_THREAD_CPUTIME_ID

/* Flag to indicate time is relative.  */
#   define TIMER_RELTIME		0
/* Flag to indicate time is absolute.  */
#   define TIMER_ABSTIME		1

#  endif

# endif	/* bits/time.h */
#endif

#if defined (__need_itimerval) && !defined (__need_timeval)
# define __need_timeval
#endif

#ifdef __need_timeval
# undef __need_timeval
# ifndef _STRUCT_TIMEVAL
#  define _STRUCT_TIMEVAL	1
#  include <bits/types.h>

/* A time value that is accurate to the nearest
   microsecond but also has a range of years.  */
struct timeval
  {
    __time_t tv_sec;		/* Seconds.  */
    __suseconds_t tv_usec;	/* Microseconds.  */
  };



# endif	/* struct timeval */
#endif	/* need timeval */

# if defined (__need_itimerval) && !defined (__itimerval_defined)
struct itimerval
  {
    /* Value to put into `it_value' when the timer expires.  */
    struct timeval it_interval;
    /* Time to the next timer expiration.  */
    struct timeval it_value;
  };
#  define __itimerval_defined
#  undef __need_itimerval
# endif

#ifndef __time_misc_defined

typedef struct timespec timespec_t;
typedef struct timespec timestruc_t;
typedef struct tm tm_t;

# define SEC		1
# define MILLISEC	1000
# define MICROSEC	1000000
# define NANOSEC	1000000000

# define __time_misc_defined

#endif /* __time_misc_defined */

#ifdef _SYSCALL32

# include <sys/types32.h>

# ifndef __time32_misc_defined

#  define TIMEVAL32_TO_TIMEVAL(tv, tv32)            \
{                                                   \
	(tv)->tv_sec = (time_t)(tv32)->tv_sec;          \
	(tv)->tv_usec = (tv32)->tv_usec;                \
}

#  define TIMEVAL_TO_TIMEVAL32(tv32, tv)            \
{                                                   \
	(tv32)->tv_sec = (time32_t)(tv)->tv_sec;        \
	(tv32)->tv_usec = (tv)->tv_usec;                \
}

#  define TIMESPEC32_TO_TIMESPEC(ts, ts32)          \
	{                                               \
		(ts)->tv_sec = (time_t)(ts32)->tv_sec;      \
		(ts)->tv_nsec = (ts32)->tv_nsec;            \
	}

#  define TIMESPEC_TO_TIMESPEC32(ts32, ts)          \
	{                                               \
	    (ts32)->tv_sec = (time32_t)(ts)->tv_sec;    \
		(ts32)->tv_nsec = (ts)->tv_nsec;            \
	}

#  define TIME32_MAX	INT32_MAX
#  define TIME32_MIN	INT32_MIN

#  define TIMESPEC_OVERFLOW(ts) \
	((ts)->tv_sec < TIME32_MIN || (ts)->tv_sec > TIME32_MAX)

#  define __time32_misc_defined
# endif /* __time32_misc_defined */

# if defined (_SYS_TIME_H) && !defined (__itimerval32_defined)
struct itimerval32
  {
	struct timeval32 it_interval;
	struct timeval32 it_value;
  };

#  define ITIMERVAL32_TO_ITIMERVAL(itv, itv32)                          \
{                                                                       \
	TIMEVAL32_TO_TIMEVAL(&(itv)->it_interval, &(itv32)->it_interval);   \
	TIMEVAL32_TO_TIMEVAL(&(itv)->it_value, &(itv32)->it_value);         \
}

#  define ITIMERVAL_TO_ITIMERVAL32(itv32, itv)                          \
{                                                                       \
	TIMEVAL_TO_TIMEVAL32(&(itv32)->it_interval, &(itv)->it_interval);   \
	TIMEVAL_TO_TIMEVAL32(&(itv32)->it_value, &(itv)->it_value);         \
}

#  define ITIMERVAL_OVERFLOW(itv)               \
	(TIMEVAL_OVERFLOW(&(itv)->it_interval) ||   \
	 TIMEVAL_OVERFLOW(&(itv)->it_value))

#  define __itimerval32_defined
# endif

# if defined (_TIME_H) && !defined (__tms32_defined)
struct tms32
  {
	clock32_t tms_utime;
	clock32_t tms_stime;
	clock32_t tms_cutime;
	clock32_t tms_cstime;
  };
#  define __tms32_defined
# endif

#endif /* _SYSCALL32 */
