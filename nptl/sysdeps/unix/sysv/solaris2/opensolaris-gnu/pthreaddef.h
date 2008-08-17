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

/* Register atfork handlers to protect signal_lock.  */
extern void sigaction_atfork (void);
#define PLATFORM_PTHREAD_INIT \
    sigaction_atfork ();

/* Additional descr fields.  */
# define PLATFORM_DESCR_FIELDS \
    int sigpipe_disabled;

/* Use tid as pthread_t (instead of descr).  */
#define PTHREAD_T_IS_TID

/* Use pthread scheduler functions in tpp.  */
#define TPP_PTHREAD_SCHED

/* pthread_setXid not supported/needed.  */
#define NO_SETXID_SUPPORT

/* Disable robust list.  */
#define NO_ROBUST_LIST_SUPPORT

/* Disable futex support.  */
#define NO_FUTEX_SUPPORT

/* Make sure SIGCANCEL sanity check compiles.  */
#define SI_TKILL SI_LWP
#define __ASSUME_CORRECT_SI_PID

/* We support tkill.  */
#undef __NR_tgkill
#undef __ASSUME_TGKILL

/* pthread_ is unsigned.  */
#define FREE_P(descr) ((descr)->tid == (pthread_t)-1)
