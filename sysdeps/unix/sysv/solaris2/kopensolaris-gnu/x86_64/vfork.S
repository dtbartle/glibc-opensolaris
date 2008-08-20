/* Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>.

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

ENTRY (__vfork)

    /* Save the return address */
    popl scratch

    /* Call vforkx(0) */
    pushl $0
    pushl $SYS_SUB_vforkx
    pushl scratch
    DO_CALL (forksys, 1)
    jb 2f
    addl $24, %rsp

    /* In the parent process, %rdx == 0, %rax == child pid.
       In the child process, %rdx == 1, %rax == parent pid. */
    decl %rdx
    andl %rdx, %rax

    /* Jump to the old return address */
    jmp *scratch

2:
    /* Restore the return address and jump to the syscall error label */
    addl $24, %rsp
    pushl scratch
    jmp SYSCALL_ERROR_LABEL

L(pseudo_end):
    ret

PSEUDO_END (__vfork)

libc_hidden_def (__vfork)
weak_alias (__vfork, vfork)
