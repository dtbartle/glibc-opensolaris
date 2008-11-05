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

#include <time.h>
#include <stdlib.h>
#include <limits.h>

int ascftime (char *s, const char *format, const struct tm *timeptr)
{
  /* If format is null use CFTIME or %C.  */
  if (!format || *format == '\0' || !(format = getenv ("CFTIME")) ||
        *format == '\0')
    format =  "%C";

  /* The caller is responsible for ensuring that the buffer is large enough.
     We just set max to INT_MAX (basically a really large number).  */
  return ((int)strftime (s, INT_MAX, format, timeptr));
}
