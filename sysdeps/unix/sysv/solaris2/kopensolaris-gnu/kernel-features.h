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

/* We don't have set_thread_area.  */
#define NO_SET_THREAD_AREA
