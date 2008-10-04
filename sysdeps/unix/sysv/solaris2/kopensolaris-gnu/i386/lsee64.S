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

ENTRY (__libc_lseek64)
    DO_CALL (llseek, 3)
    jnb 1f
    ret
1:
    jmp SYSCALL_ERROR_LABEL

L(pseudo_end):

    /* set the upper-64 bits to -1 */
    orl $-1, %edx;
    ret
PSEUDO_END (__libc_lseek64)

libc_hidden_def (__libc_lseek64)
weak_alias (__libc_lseek64, __lseek64)
weak_alias (__libc_lseek64, lseek64)
