/* PLT trampolines.  PPC32 version.
   Copyright (C) 2005 Free Software Foundation, Inc.
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

#include <sysdep.h>

	.section ".text"
	.align 2
	.globl _dl_runtime_resolve
	.type _dl_runtime_resolve,@function
_dl_runtime_resolve:
 # We need to save the registers used to pass parameters, and register 0,
 # which is used by _mcount; the registers are saved in a stack frame.
	stwu r1,-64(r1)
	stw r0,12(r1)
	stw r3,16(r1)
	stw r4,20(r1)
 # The code that calls this has put parameters for `fixup' in r12 and r11.
	mr r3,r12
	stw r5,24(r1)
	mr r4,r11
	stw r6,28(r1)
	mflr r0
 # We also need to save some of the condition register fields
	stw r7,32(r1)
	stw r0,48(r1)
	stw r8,36(r1)
	mfcr r0
	stw r9,40(r1)
	stw r10,44(r1)
	stw r0,8(r1)
	bl _dl_fixup@local
 # 'fixup' returns the address we want to branch to.
	mtctr r3
 # Put the registers back...
	lwz r0,48(r1)
	lwz r10,44(r1)
	lwz r9,40(r1)
	mtlr r0
	lwz r8,36(r1)
	lwz r0,8(r1)
	lwz r7,32(r1)
	lwz r6,28(r1)
	mtcrf 0xFF,r0
	lwz r5,24(r1)
	lwz r4,20(r1)
	lwz r3,16(r1)
	lwz r0,12(r1)
 # ...unwind the stack frame, and jump to the PLT entry we updated.
	addi r1,r1,64
	bctr
	.size	 _dl_runtime_resolve,.-_dl_runtime_resolve

	.align 2
	.globl _dl_prof_resolve
	.type _dl_prof_resolve,@function
_dl_prof_resolve:
 # We need to save the registers used to pass parameters, and register 0,
 # which is used by _mcount; the registers are saved in a stack frame.
	stwu r1,-64(r1)
        stw r0,12(r1)
	stw r3,16(r1)
	stw r4,20(r1)
 # The code that calls this has put parameters for `fixup' in r12 and r11.
	mr r3,r12
	stw r5,24(r1)
	mr r4,r11
	stw r6,28(r1)
	mflr r5
 # We also need to save some of the condition register fields.
	stw r7,32(r1)
	stw r5,48(r1)
	stw r8,36(r1)
	mfcr r0
	stw r9,40(r1)
	stw r10,44(r1)
	stw r0,8(r1)
	bl _dl_profile_fixup@local
 # 'fixup' returns the address we want to branch to.
	mtctr r3
 # Put the registers back...
	lwz r0,48(r1)
	lwz r10,44(r1)
	lwz r9,40(r1)
	mtlr r0
	lwz r8,36(r1)
	lwz r0,8(r1)
	lwz r7,32(r1)
	lwz r6,28(r1)
	mtcrf 0xFF,r0
	lwz r5,24(r1)
	lwz r4,20(r1)
	lwz r3,16(r1)
        lwz r0,12(r1)
 # ...unwind the stack frame, and jump to the PLT entry we updated.
	addi r1,r1,64
	bctr
	.size	 _dl_prof_resolve,.-_dl_prof_resolve
