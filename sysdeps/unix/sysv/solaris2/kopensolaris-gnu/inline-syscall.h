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

#ifndef _INLINE_SYSCALL_H
#define _INLINE_SYSCALL_H

#include <sys/types.h>
#include <syscallP.h>
#include <sysdep.h>

typedef union rval
{
    struct
    {
        int32_t __rval1;
        int32_t __rval2;
    } rvals;
    int64_t rval64;
} rval_t;
#define rval1	rvals.__rval1
#define rval2	rvals.__rval2

#endif /* _INLINE_SYSCALL_H */
