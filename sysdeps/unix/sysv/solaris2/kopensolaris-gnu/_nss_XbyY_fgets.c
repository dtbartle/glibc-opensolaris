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

#include <nssP.h>
#include <string.h>

void _nss_XbyY_fgets (FILE *fp, nss_XbyY_args_t *args)
{
  args->returnval = 0;
  args->erange = 0;

  /* Read a line, ignoring lines that are too long.  */
  char buf[LINE_MAX + 2];
  if (!fgets (buf, sizeof (buf), fp))
    return;
  size_t len = strlen (buf);
  if (len > LINE_MAX)
    {
      /* Read rest of line.  */
      while (buf[len - 1] != '\n' && fgets (buf, sizeof (buf), fp))
        len = strlen (buf);
      args->erange = 1;
      return;
    }
  if (buf[len - 1] == '\n')
    buf[len - 1] = '\0';

  /* Parse the line.  */
  int res = (*args->str2ent) (buf, strlen (buf), args->buf.result,
      args->buf.buffer, args->buf.buflen);
  if (res == NSS_STR_PARSE_SUCCESS)
    args->returnval = args->buf.result;
  else if (res == NSS_STR_PARSE_ERANGE)
    args->erange = 1;
}
