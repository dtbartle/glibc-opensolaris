/* Copyright (C) 2002, 2003, 2004, 2005, 2007 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper <drepper@redhat.com>, 2002.

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
#include <shlib-compat.h>
#include <lowlevellock.h>
#include <lowlevelcond.h>
#include <kernel-features.h>
#include <pthread-errnos.h>


	.text

	/* int pthread_cond_signal (pthread_cond_t *cond) */
	.globl	__pthread_cond_signal
	.type	__pthread_cond_signal, @function
	.align	16
__pthread_cond_signal:

	pushl	%ebx
	pushl	%edi

	movl	12(%esp), %edi

	/* Get internal lock.  */
	movl	$1, %edx
	xorl	%eax, %eax
	LOCK
#if cond_lock == 0
	cmpxchgl %edx, (%edi)
#else
	cmpxchgl %edx, cond_lock(%edi)
#endif
	jnz	1f

2:	leal	cond_futex(%edi), %ebx
	movl	total_seq+4(%edi), %eax
	movl	total_seq(%edi), %ecx
	cmpl	wakeup_seq+4(%edi), %eax
#if cond_lock != 0
	/* Must use leal to preserve the flags.  */
	leal	cond_lock(%edi), %edi
#endif
	ja	3f
	jb	4f
	cmpl	wakeup_seq-cond_futex(%ebx), %ecx
	jbe	4f

	/* Bump the wakeup number.  */
3:	addl	$1, wakeup_seq-cond_futex(%ebx)
	adcl	$0, wakeup_seq-cond_futex+4(%ebx)
	addl	$1, (%ebx)

	/* Wake up one thread.  */
	pushl	%esi
	pushl	%ebp
#if FUTEX_PRIVATE_FLAG > 255
	xorl	%ecx, %ecx
#endif
	cmpl	$-1, dep_mutex-cond_futex(%ebx)
	sete	%cl
	subl	$1, %ecx
#ifdef __ASSUME_PRIVATE_FUTEX
	andl	$FUTEX_PRIVATE_FLAG, %ecx
#else
	andl	%gs:PRIVATE_FUTEX, %ecx
#endif
	addl	$FUTEX_WAKE_OP, %ecx
	movl	$SYS_futex, %eax
	movl	$1, %edx
	movl	$1, %esi
	movl	$FUTEX_OP_CLEAR_WAKE_IF_GT_ONE, %ebp
	/* FIXME: Until Ingo fixes 4G/4G vDSO, 6 arg syscalls are broken for
	   sysenter.
	ENTER_KERNEL  */
	int	$0x80
	popl	%ebp
	popl	%esi

	/* For any kind of error, we try again with WAKE.
	   The general test also covers running on old kernels.  */
	cmpl	$-4095, %eax
	jae	7f

6:	xorl	%eax, %eax
	popl	%edi
	popl	%ebx
	ret

7:	/* %ecx should be either FUTEX_WAKE_OP or
	   FUTEX_WAKE_OP|FUTEX_PRIVATE_FLAG from the previous syscall.  */
	xorl	$(FUTEX_WAKE ^ FUTEX_WAKE_OP), %ecx
	movl	$SYS_futex, %eax
	/* %edx should be 1 already from $FUTEX_WAKE_OP syscall.
	movl	$1, %edx  */
	ENTER_KERNEL

	/* Unlock.  Note that at this point %edi always points to
	   cond_lock.  */
4:	LOCK
	subl	$1, (%edi)
	je	6b

	/* Unlock in loop requires wakeup.  */
5:	movl	%edi, %eax
#if (LLL_SHARED-LLL_PRIVATE) > 255
	xorl	%ecx, %ecx
#endif
	cmpl	$-1, dep_mutex-cond_futex(%ebx)
	setne	%cl
	subl	$1, %ecx
	andl	$(LLL_SHARED-LLL_PRIVATE), %ecx
#if LLL_PRIVATE != 0
	addl	$LLL_PRIVATE, %ecx
#endif
	call	__lll_unlock_wake
	jmp	6b

	/* Initial locking failed.  */
1:
#if cond_lock == 0
	movl	%edi, %edx
#else
	leal	cond_lock(%edi), %edx
#endif
#if (LLL_SHARED-LLL_PRIVATE) > 255
	xorl	%ecx, %ecx
#endif
	cmpl	$-1, dep_mutex(%edi)
	setne	%cl
	subl	$1, %ecx
	andl	$(LLL_SHARED-LLL_PRIVATE), %ecx
#if LLL_PRIVATE != 0
	addl	$LLL_PRIVATE, %ecx
#endif
	call	__lll_lock_wait
	jmp	2b

	.size	__pthread_cond_signal, .-__pthread_cond_signal
versioned_symbol (libpthread, __pthread_cond_signal, pthread_cond_signal,
		  GLIBC_2_3_2)
