/* Declaration of ucontext_t.
   Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_UCONTEXT_H
#define _SYS_UCONTEXT_H	1

#ifndef __stack_t_defined
# define __need_stack_t
# include <bits/sigstack.h>
#endif
#include <bits/sigset.h>
#include <sys/regset.h>
#include <features.h>

typedef struct ucontext
{
    unsigned long uc_flags;
    struct ucontext *uc_link;
    __sigset_t uc_sigmask;
    stack_t uc_stack;
    mcontext_t uc_mcontext;
    long uc_filler[5];
} ucontext_t;

/* uc_flags */
#define UC_SIGMASK	0x01
#define UC_STACK	0x02
#define UC_CPU		0x04
#define UC_MAU		0x08
#define UC_FPU		UC_MAU
#define UC_MCONTEXT	(UC_CPU | UC_FPU)
#define UC_ALL		(UC_SIGMASK | UC_STACK | UC_MCONTEXT)

#define GETCONTEXT	0
#define SETCONTEXT	1
#define GETUSTACK	2
#define SETUSTACK	3

__BEGIN_DECLS

int getustack (stack_t **);

int setustack (stack_t *);

int stack_getbounds (stack_t *);

__END_DECLS

#endif /* _SYS_UCONTEXT_H */
