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

/* Grow the break. First align the current break to low_align, then
   add min_size and finally align on high_align. Return the low-aligned
   break value and set actual_size to the difference of the resulting break
   value and the low-aligned break value.  */

#include <unistd.h>
#include <errno.h>

extern void *__curbrk;

void *_sbrk_grow_aligned (size_t min_size, size_t low_align, size_t high_align,
      size_t *actual_size)
{
  if (!__curbrk)
    {
      /* Try to initialize the break.  */
      if (sbrk (0) == (void *)-1)
        {
          __set_errno (ENOTSUP);
          return (void *)-1;
        }
    }

  /* low_align and high_align must be powers of 2.  */
  if ((low_align & (low_align - 1)) != 0 ||
        (high_align & (high_align - 1)) != 0)
    {
      __set_errno (EINVAL);
      return (void *)-1;
    }

  uintptr_t lowbrk = ((uintptr_t)__curbrk + (low_align - 1)) & ~(low_align - 1);
  uintptr_t highbrk = (lowbrk + min_size + (high_align - 1)) & ~(high_align - 1);

  if (brk ((void *)highbrk) != 0)
    return (void *)-1;

  if (actual_size)
    *actual_size = (size_t)(highbrk - lowbrk);

  return (void *)lowbrk;
}
