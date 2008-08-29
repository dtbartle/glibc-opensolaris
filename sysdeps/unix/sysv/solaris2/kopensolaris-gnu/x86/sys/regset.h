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

#ifndef _SYS_REGSET_H
#define _SYS_REGSET_H	1

#include <features.h>

#ifdef __USE_MISC

#include <bits/regset.h>

#ifdef __amd64__

# define REG_R15	0
# define REG_R14	1
# define REG_R13	2
# define REG_R12	3
# define REG_R11	4
# define REG_R10	5
# define REG_R9		6
# define REG_R8		7
# define REG_RDI	8
# define REG_RSI	9
# define REG_RBP	10
# define REG_RBX	11
# define REG_RDX	12
# define REG_RCX	13
# define REG_RAX	14
# define REG_TRAPNO	15
# define REG_ERR	16
# define REG_RIP	17
# define REG_CS		18
# define REG_RFL	19
# define REG_RSP	20
# define REG_SS		21
# define REG_FS		22
# define REG_GS		23
# define REG_ES		24
# define REG_DS		25
# define REG_FSBASE	26
# define REG_GSBASE	27

# define REG_PC		REG_RIP
# define REG_FP		REG_RBP
# define REG_SP		REG_RSP
# define REG_PS		REG_RFL
# define REG_R0		REG_RAX
# define REG_R1		REG_RDX

#else /* __i386__ */

# define GS	0
# define FS	1
# define ES	2
# define DS	3
# define EDI	4
# define ESI	5
# define EBP	6
# define ESP	7
# define EBX	8
# define EDX	9
# define ECX	10
# define EAX	11
# define TRAPNO	12
# define ERR	13
# define EIP	14
# define CS	15
# define EFL	16
# define UESP	17
# define SS	18

# define REG_PC		EIP
# define REG_FP		EBP
# define REG_SP		UESP
# define REG_PS		EFL
# define REG_R0		EAX
# define REG_R1		EDX

#endif /* __amd64__ */

#endif

#endif /* _SYS_REGSET_H */
