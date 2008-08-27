/* sigstack, sigaltstack definitions. OpenSolaris version.
   Copyright (C) 1998, 1999, 2008 Free Software Foundation, Inc.
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

#if !defined(_SIGNAL_H) && !defined(__need_stack_t)
# error "Never include this file directly.  Use <signal.h> instead"
#endif

#include <bits/types.h>

#if !defined(__need_stack_t)

/* Structure describing a signal stack (obsolete).  */
struct sigstack
  {
    void *ss_sp;		/* Signal stack pointer.  */
    int ss_onstack;		/* Nonzero if executing on this stack.  */
  };


/* Possible values for `ss_flags.'.  */
enum
{
  SS_ONSTACK = 1,
#define SS_ONSTACK	SS_ONSTACK
  SS_DISABLE = 2
#define SS_DISABLE	SS_DISABLE
};

/* Minimum stack size for a signal handler.  */
#define MINSIGSTKSZ	2048

/* System default stack size.  */
#define SIGSTKSZ	8192

#endif /* __need_stack_t */

#if !defined(__stack_t_defined)
# define __stack_t_defined
# undef __need_stack_t

/* Alternate, preferred interface.  */
typedef struct sigaltstack
  {
    void *ss_sp;
    __SIZE_TYPE__ ss_size;
    int ss_flags;
  } stack_t;

#endif /* !defined(__stack_t_defined) */
