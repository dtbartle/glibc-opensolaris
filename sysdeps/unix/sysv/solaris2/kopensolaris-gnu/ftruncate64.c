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

#include <not-cancel.h>
#include <sys/types.h>
#include <sys/fcntl.h>

int
__ftruncate64 (int fd, off64_t length)
{
    struct flock64 fl;
    fl.l_whence = 0;
    fl.l_len = 0;
    fl.l_start = length;
    fl.l_type = F_WRLCK;

    return fcntl_not_cancel (fd, F_FREESP64, &fl);
}

weak_alias (__ftruncate64, ftruncate64)
