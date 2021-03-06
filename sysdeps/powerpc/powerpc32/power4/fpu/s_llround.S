/* llround function.  PowerPC32 on PowerPC64 version.
   Copyright (C) 2004, 2006 Free Software Foundation, Inc.
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
   Software Foundation, Inc., 1 Franklin Street, Fifth Floor, Boston MA
   02110-1301 USA.  */

#include <sysdep.h>
#include <math_ldbl_opt.h>

	.section	.rodata.cst8,"aM",@progbits,8
	.align	2
.LC0:	/* 0.0 */
	.long 0x00000000
.LC1:	/* 0.5 */
	.long 0x3f000000

	.section	".text"
	
/* long [r3] lround (float x [fp1])
   IEEE 1003.1 lround function.  IEEE specifies "round to the nearest 
   integer value, rounding halfway cases away from zero, regardless of
   the current rounding mode."  However PowerPC Architecture defines
   "round to Nearest" as "Choose the best approximation. In case of a 
   tie, choose the one that is even (least significant bit o).". 
   So we can't use the PowerPC "round to Nearest" mode. Instead we set
   "round toward Zero" mode and round by adding +-0.5 before rounding
   to the integer value.  */

ENTRY (__llround)
	stwu    r1,-16(r1)
	cfi_adjust_cfa_offset (16)
#ifdef SHARED
	mflr	r11
	cfi_register(lr,r11)
# ifdef HAVE_ASM_PPC_REL16
	bcl	20,31,1f
1:	mflr	r9
	addis	r9,r9,.LC0-1b@ha
	addi	r9,r9,.LC0-1b@l
# else
	bl	_GLOBAL_OFFSET_TABLE_@local-4
	mflr	r10
	lwz	r9,.LC0@got(10)
# endif
	mtlr	r11
	cfi_same_value (lr)
	lfs	fp12,0(r9)
	lfs	fp10,.LC1-.LC0(r9)
#else
	lis	r9,.LC0@ha
	lis	r10,.LC1@ha
	lfs	fp12,.LC0@l(r9)
	lfs	fp10,.LC1@l(r10)
#endif
	fcmpu	cr6,fp1,fp12	/* if (x > 0.0)  */
	ble-	cr6,.L4
	fadd	fp1,fp1,fp10	/* x+= 0.5;  */
.L9:
	fctidz	fp2,fp1		/* Convert To Integer DW round toward 0.  */
	stfd	fp2,8(r1)
	nop	/* Ensure the following load is in a different dispatch  */
	nop	/* group to avoid pipe stall on POWER4&5.  */
	nop
	lwz	r4,12(r1)
	lwz	r3,8(r1)
	addi	r1,r1,16
	blr
.L4:
	fsub	fp1,fp1,fp10	/* x-= 0.5;  */
	b	.L9
	END (__llround)

weak_alias (__llround, llround)

strong_alias (__llround, __llroundf)
weak_alias (__llround, llroundf)

#ifdef NO_LONG_DOUBLE
weak_alias (__llround, llroundl)
strong_alias (__llround, __llroundl)
#endif
#if LONG_DOUBLE_COMPAT(libm, GLIBC_2_1)
compat_symbol (libm, __llround, llroundl, GLIBC_2_1)
#endif
