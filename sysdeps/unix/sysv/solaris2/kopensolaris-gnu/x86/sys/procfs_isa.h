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

#ifdef __i386__
# define R_PC	EIP
# define R_PS	EFL
# define R_SP	UESP
# define R_FP	EBP
# define R_R0	EAX
# define R_R1	EDX
#else
# define R_PC	REG_RIP
# define R_PS	REG_RFL
# define R_SP	REG_RSP
# define R_FP	REG_RBP
# define R_R0	REG_RAX
# define R_R1	REG_RDX
#endif

#endif /* _SYS_PROCFS_ISA_H */
