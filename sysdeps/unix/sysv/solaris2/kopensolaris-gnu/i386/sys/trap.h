/* Declaration of traps.
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

#ifndef _SYS_TRAP_H
#define _SYS_TRAP_H

/* traps */
#define T_ZERODIV		0x0
#define T_SGLSTP		0x1
#define T_NMIFLT		0x2
#define T_BPTFLT		0x3
#define T_OVFLW			0x4
#define T_BOUNDFLT		0x5
#define T_ILLINST		0x6
#define T_NOEXTFLT		0x7
#define T_DBLFLT		0x8
#define T_EXTOVRFLT		0x9
#define T_TSSFLT		0xa
#define T_SEGFLT		0xb
#define T_STKFLT		0xc
#define T_GPFLT			0xd
#define T_PGFLT			0xe
#define T_EXTERRFLT		0x10
#define T_ALIGNMENT		0x11
#define T_MCE			0x12
#define T_SIMDFPE		0x13
#define T_DBGENTR		0x14
#define T_ENDPERR		0x21
#define T_ENOEXTFLT		0x20
#define T_FASTTRAP		0xd2
#define T_SYSCALLINT	0x91
#define T_DTRACE_RET	0x7f
#define T_INT80			0x80
#define T_SOFTINT		0x50fd

/* fast traps */
#define T_FNULL			0
#define T_FGETFP		1
#define T_FSETFP		2
#define T_GETHRTIME		3
#define T_GETHRVTIME	4
#define T_GETHRESTIME	5
#define T_GETLGRP		6

#endif /* _SYS_TRAP_H */
