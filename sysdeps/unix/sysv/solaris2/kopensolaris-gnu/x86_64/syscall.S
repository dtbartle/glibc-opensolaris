/* Copyright (C) 2006 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Modification for FreeBSD contributed by Petr Salinger, 2006.

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
	popl %rcx	/* Pop return address into %rcx.  */
	popl %eax	/* Pop syscall number into %eax. */
	pushl %rcx	/* Push back return adderss.  */
	syscall	/* Do the system call.  */
	pushl %rcx	/* Push back return address.  */
	jb SYSCALL_ERROR_LABEL;	/* Jump to error handler if error.  */

L(pseudo_end):
	ret			/* Return to caller.  */
PSEUDO_END (__syscall)
weak_alias (__syscall, syscall)

	  .text;
ENTRY (__systemcall)
	popl %rdx		/* Pop return address into %edx.  */
	popl %rcx		/* Pop sysret_t into %rcx.  */
	popl %eax		/* Pop syscall number into %eax.  */
	pushl %rdx		/* Push return address onto stack.  */
	syscall		/* Do the system call.  */
	pushl %rcx		/* Restore sysret_t on stack.  */
	movl 8(%rsp), %rdx	/* Save return address into %rdx.  */
	pushl %rdx		/* Restore return address on stack.  */
	jb 1f			/* Jump to error handler if error.  */
	movl %rax, 0(%rcx)	/* Set sysret_t.  */
	xorl %rax, %rax		/* Set return to 0.  */
1:
	ret
PSEUDO_END (__syscall)
