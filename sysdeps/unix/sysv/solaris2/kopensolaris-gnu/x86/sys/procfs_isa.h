/* Declarations of x86 (i386 and amd64) procfs structs and macros.
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

#ifndef _SYS_PROCFS_ISA_H
#define _SYS_PROCFS_ISA_H

#include <sys/regset.h>
#include <sys/isa_defs.h>

#define PR_MODEL_UNKNOWN	0
#define PR_MODEL_ILP32		1
#define PR_MODEL_LP64		2

#ifdef _LP64
# define PR_MODEL_NATIVE	PR_MODEL_LP64
#else
# define PR_MODEL_NATIVE	PR_MODEL_ILP32
#endif

typedef unsigned char instr_t;

#define prgregset_t	gregset_t
#define prfpregset_t	fpregset_t
#define prgreg_t	greg_t
#define prfpregset	fpu

#define NPRGREG	_NGREG

#ifdef _SYSCALL32

typedef unsigned char instr32_t;

# if defined(__amd64)
#  define NPRGREG32		_NGREG32
#  define prgreg32_t		greg32_t
#  define prgregset32_t		gregset32_t
#  define prfpregset32		fpu32
#  define prfpregset32_t	fpregset32_t
# else
#  define NPRGREG32		_NGREG
#  define prgreg32_t		greg_t
#  define prgregset32_t		gregset_t
#  define prfpregset32		fpu
#  define prfpregset32_t	fpregset_t
# endif

#endif /* _SYSCALL32 */

#ifdef __amd64__
# define R_PC	REG_RIP
# define R_PS	REG_RFL
# define R_SP	REG_RSP
# define R_FP	REG_RBP
# define R_R0	REG_RAX
# define R_R1	REG_RDX
#else
# define R_PC	EIP
# define R_PS	EFL
# define R_SP	UESP
# define R_FP	EBP
# define R_R0	EAX
# define R_R1	EDX
#endif

#endif /* _SYS_PROCFS_ISA_H */
