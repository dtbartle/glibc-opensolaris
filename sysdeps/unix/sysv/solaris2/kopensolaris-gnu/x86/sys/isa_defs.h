/* Declarations of x86 (i386 and amd64) macros.
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

#ifndef _SYS_ISA_DEFS_H
#define _SYS_ISA_DEFS_H

#define _LITTLE_ENDIAN
#define _STACK_GROWS_DOWNWARD
#define _LONG_LONG_LTOH
#define _BIT_FIELDS_LTOH
#define _IEEE_754
#define _CHAR_IS_SIGNED
#define _BOOL_ALIGNMENT		1
#define _CHAR_ALIGNMENT		1
#define _SHORT_ALIGNMENT	2
#define _INT_ALIGNMENT		4
#define _FLOAT_ALIGNMENT	4
#define _FLOAT_COMPLEX_ALIGNMENT	4

#ifdef __amd64__
# define _LONG_ALIGNMENT	8
# define _LONG_LONG_ALIGNMENT	8
# define _DOUBLE_ALIGNMENT	8
# define _DOUBLE_COMPLEX_ALIGNMENT	8
# define _LONG_DOUBLE_ALIGNMENT	16
# define _LONG_DOUBLE_COMPLEX_ALIGNMENT	16
# define _POINTER_ALIGNMENT	8
# define _MAX_ALIGNMENT		16
# define _ALIGNMENT_REQUIRED	1
# define _LP64
# define _MULTI_DATAMODEL
# define __i386_COMPAT
#else /* __i386__ */
# define _LONG_ALIGNMENT	4
# define _LONG_LONG_ALIGNMENT	4
# define _DOUBLE_ALIGNMENT	4
# define _DOUBLE_COMPLEX_ALIGNMENT	4
# define _LONG_DOUBLE_ALIGNMENT	4
# define _LONG_DOUBLE_COMPLEX_ALIGNMENT	4
# define _POINTER_ALIGNMENT	4
# define _MAX_ALIGNMENT		4
# define _ALIGNMENT_REQUIRED	0
# define _ILP32
#endif /* __amd64__ */

#define _LONG_LONG_ALIGNMENT_32	4
#define _SUNOS_VTOC_16
#define _DMA_USES_PHYSADDR
#define _FIRMWARE_NEEDS_FDISK
#define _PSM_MODULES
#define _RTC_CONFIG
#define _DONT_USE_1275_GENERIC_NAMES
#define _HAVE_CPUID_INSN

#endif /* _SYS_ISA_DEFS_H */
