/* Definition for thread-local data handling.  OpenSolaris/i386 version.
   Copyright (C) 2002, 2003, 2004, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

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

#ifndef _OPENSOLARIS_TLS_H
#define _OPENSOLARIS_TLS_H 1

/* __thread doesn't work for statically-linked executables.  */
#if !defined (SHARED)
# undef HAVE___THREAD
#endif

/* We can use most of the code from the nptl tls.h.  */
#include_next <tls.h>

#ifndef __ASSEMBLER__

/* OpenSolaris has lwp_private in order to set the thread data.  */
# include <sys/lwp.h>
# include <sys/syscall.h>

# undef TLS_INIT_TP
# define TLS_INIT_TP(thrdescr, secondcall) \
  ({ void *_thrdescr = (thrdescr);					      \
     tcbhead_t *_head = _thrdescr;					      \
     int _result;							      \
     sysret_t ret;                                          \
									      \
     _head->tcb = _thrdescr;						      \
     /* For now the thread descriptor is at the same address.  */	      \
     _head->self = _thrdescr;						      \
     /* New syscall handling support.  */				      \
     INIT_SYSINFO;							      \
                                                                    \
     (__systemcall (&ret, SYS_lwp_private, _LWP_SETPRIVATE, _LWP_GSBASE,       \
       (uintptr_t)_thrdescr) != 0)            \
       ? "lwp_private failed when setting up thread-local storage\n" : NULL; \
  })

/* TODO: Figure out what to define this as.  */
# undef DB_THREAD_SELF

# endif /* __ASSEMBLER__ */

#endif /* _OPENSOLARIS_TLS_H */
