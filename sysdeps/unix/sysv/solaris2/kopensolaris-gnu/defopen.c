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

#include <defltP.h>
#include <deflt.h>
#include <stdio.h>
#include <stdlib.h>

_DEFLT_INIT

int defopen (fn)
      char *fn;
{
  /* Close old file if open.  */
  if (_DEFLT (fp))
    fclose (_DEFLT (fp));
  if (fn == NULL)
    return 0;

  _DEFLT (fp) = fopen (fn, "r");
  if (!_DEFLT (fp))
    return -1;

  /* Allocate line buffer.  */
  if (_DEFLT (buf) == NULL)
    {
      _DEFLT (buf) = malloc (_DEFLT_BUFSIZE);
      if (!_DEFLT (buf))
        return -1;
    }

  /* Set default flags.  */
  _DEFLT (flags) = DC_STD;

  return 0;
}
