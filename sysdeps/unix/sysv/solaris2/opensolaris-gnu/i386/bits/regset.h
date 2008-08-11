/* Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _BITS_REGSET_H
#define _BITS_REGSET_H	1

#include <features.h>
#include <bits/types.h>

typedef struct __fpu
{
	union
	{
		struct __fpchip_state
		{
			__uint32_t __state[27];
			__uint32_t __status;
			__uint32_t __mxcsr;
			__uint32_t __xstatus;
			__uint32_t __pad[2];
			__uint32_t __xmm[4][8];
		} __fpchip_state;
		struct __fp_emul_space
		{
			__uint8_t __fp_emul[246];
			__uint8_t __fp_epad[2];
		} __fp_emul_space;
		__uint32_t __f_fpregs[95];
	} __fp_reg_set;
} fpregset_t;

# define _NGREG		28
# define NGREG		_NGREG

typedef int greg_t;

# define prgregset_t	gregset_t
# define prfpregset_t	fpregset_t

typedef greg_t gregset_t[_NGREG];

typedef struct {
    gregset_t gregs;
    fpregset_t fpregs;
} mcontext_t;

#endif /* _SYS_REGSET_H */
