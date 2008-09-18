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

/* Docs: http://docs.sun.com/app/docs/doc/819-2243/reboot-3c?l=en&a=view */

#include <sys/types.h>
#include <sys/reboot.h>
#include <uadminP.h>
#include <bp-checks.h>

int
reboot (howto, bootargs)
     int howto;
     char *bootargs;
{
  /* compute cmd */
  int cmd;
  if (howto & RB_DUMP)
      cmd = A_DUMP;
  else
      cmd = A_SHUTDOWN;

  /* compute fcn */
  int fcn;
  if (howto & RB_ASKNAME)
    if (howto & RB_SINGLE)
      fcn = AD_SIBOOT;
    else
      fcn = AD_IBOOT;
  else if (howto & RB_HALT)
      fcn = AD_HALT;
  else
    if (howto & RB_SINGLE)
      fcn = AD_SBOOT;
    else
      fcn = AD_BOOT;

  return uadmin (cmd, fcn, (uintptr_t)CHECK_1 (bootargs));
}
