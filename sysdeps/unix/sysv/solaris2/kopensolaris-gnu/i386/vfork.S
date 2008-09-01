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

ENTRY (__vfork)

    /* save the return address */
    popl %ecx; cfi_adjust_cfa_offset (-4)

    /* call vforkx(0) */
    pushl $0; cfi_adjust_cfa_offset (4)
    pushl $SYS_SUB_vforkx; cfi_adjust_cfa_offset (4)
    pushl %ecx; cfi_adjust_cfa_offset (4)
    DO_CALL (forksys, 1)
    jb 2f

    /* pop vforkx args */
    addl $12, %esp; cfi_adjust_cfa_offset (-12)

    /* In the parent process, %edx == 0, %eax == child pid.
       In the child process, %edx == 1, %eax == parent pid. */
    decl %edx
    andl %edx, %eax

    /* jump to the old return address */
    jmp *%ecx

2:
    /* pop vforkx args */
    addl $12, %esp; cfi_adjust_cfa_offset (-12)

    /* restore the return address and jump to the syscall error label */
    pushl %ecx; cfi_adjust_cfa_offset (4)
    jmp SYSCALL_ERROR_LABEL

L(pseudo_end):
    ret

PSEUDO_END (__vfork)

libc_hidden_def (__vfork)
weak_alias (__vfork, vfork)
