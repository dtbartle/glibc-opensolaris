/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>, 2008.

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

#include <ucontext_i.h>

ENTRY(__swapcontext)

    /* load ucp (arg) into %ecx */
    movl 4(%esp), %ecx

    /* load return address into %eax */
    movl 0(%esp), %eax

    /* push ucp, subcall number, and return address */
    pushl %ecx
    pushl $SYS_SUB_getcontext
    pushl %eax

    /* call context syscall */
    DO_CALL(context, 2)
    jnb 1f

    /* pop args from stack */
    addl $12, %esp

    /* jump to error label */
    jmp SYSCALL_ERROR_LABEL

1:
    /* pop args from stack */
    addl $12, %esp

    /* load ucp (arg) into %ecx */
    movl 4(%esp), %ecx

    /* save %esp */
    leal 4(%esp), %eax
    movl %eax, oUESP(%ecx)

    /* save %eip */
    movl 0(%esp), %eax
    movl %eax, oEIP(%ecx)

    /* return 0 on success */
    xorl %eax, %eax
    movl %eax, oEAX(%ecx)

    /* load ocp (arg 2) into %edx */
    movl 8(%esp), %edx

    /* push ucp */
    pushl %edx

    /* call __setcontext */
    call __setcontext

    /* pop ucp */
    addl $4, %esp

    /* __setcontext sets the return (%eax) */
L(pseudo_end):
    ret

PSEUDO_END(__swapcontext)

weak_alias (__swapcontext, swapcontext)
