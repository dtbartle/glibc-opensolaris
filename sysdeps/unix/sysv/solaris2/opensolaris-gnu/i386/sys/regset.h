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

# define GS		0
# define FS		1
# define ES		2
# define DS		3
# define EDI		4
# define ESI		5
# define EBP		6
# define ESP		7
# define EBX		8
# define EDX		9
# define ECX		10
# define EAX		11
# define TRAPNO	12
# define ERR		13
# define EIP		14
# define CS		15
# define EFL		16
# define UESP	17
# define SS		18

#endif

#endif /* _SYS_REGSET_H */
