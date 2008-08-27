/* Copyright (C) 1993, 1995-1998, 2002, 2008 Free Software Foundation, Inc.
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

	  .text;
ENTRY (__syscall)
	popl %ecx	/* Pop return address into %ecx.  */
	popl %eax	/* Pop syscall number into %eax. */
	pushl %ecx	/* Push back return adderss.  */
	cfi_adjust_cfa_offset (-4)
	int $0x91	/* Do the system call.  */
	pushl %ecx	/* Push back return address.  */
	cfi_adjust_cfa_offset (4)
	jb SYSCALL_ERROR_LABEL;	/* Jump to error handler if error.  */

L(pseudo_end):
	ret			/* Return to caller.  */
PSEUDO_END (__syscall)
weak_alias (__syscall, syscall)

	  .text;
ENTRY (__systemcall)
	popl %edx		/* Pop return address into %edx.  */
	popl %ecx		/* Pop sysret_t into %ecx.  */
	popl %eax		/* Load syscall number into %eax.  */
	pushl %edx		/* Push return address onto stack.  */
	cfi_adjust_cfa_offset (-8)
	int $0x91		/* Do the system call.  */
	pushl %ecx		/* Restore sysret_t on stack.  */
	movl 4(%esp), %edx	/* Save return address into %edx.  */
	pushl %edx		/* Restore return address on stack.  */
	cfi_adjust_cfa_offset (8)
	jb 1	/* Jump to error handler if error.  */
	movl %eax, 0(%ecx)	/* Set first 4 bytes of sysret_t.  */
	movl %edx, 4(%ecx)	/* Set second 4 bytes of sysret_t.  */
	xorl %eax, %eax		/* Set return to 0.  */
	ret
1:
	orl $-1, 0(%ecx)	/* Set first 4 bytes of sysret_t.  */
	orl $-1, 4(%ecx)	/* Set second 4 bytes of sysret_t.  */
	ret
PSEUDO_END (__syscall)
