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

#include <inline-syscall.h>
#include <sys/pset.h>

DECLARE_INLINE_SYSCALL (int, pset_getloadavg, int *buf, int nelem);

int
pset_getloadavg (psetid_t pset, double loadavg[], int nelem)
{
  int buf[3], i;

  if (nelem > 3)
    nelem = 3;
  int result = INLINE_SYSCALL (pset_getloadavg, 2, buf, nelem);
  if (result == -1)
    return -1;

  /* the results from the kernel are scaled by a factor of 256 */
  for(i = 0; i < nelem; i++)
    loadavg[i] = (double)buf[i] / 256;

  return nelem;
}
