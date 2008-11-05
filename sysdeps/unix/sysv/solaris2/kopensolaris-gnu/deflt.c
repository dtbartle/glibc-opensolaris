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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static __thread FILE *deflt_fp = NULL;
static __thread int deflt_flags = 0;
static __thread char deflt_buf[_DEFLT_BUFSIZE];


int defopen (char *fn)
{
  /* Close old file if open.  */
  if (deflt_fp)
    {
      fclose (deflt_fp);
      deflt_fp = NULL;
    }
  if (!fn)
    return 0;

  deflt_fp = fopen (fn, "r");
  if (!deflt_fp)
    return -1;

  /* Set default flags.  */
  deflt_flags = DC_STD;

  return 0;
}


char * defread (char *cp)
{
  if (!deflt_fp)
      return NULL;

  /* Rewind if needed.  */
  if ((deflt_flags & DC_NOREWIND) == 0)
    rewind (deflt_fp);

  size_t cplen = strlen (cp);
  int (*strcmpfunc)(const char *, const char *, size_t) =
      (deflt_flags & DC_CASE) ? strncmp : strncasecmp;
  while (fgets (deflt_buf, _DEFLT_BUFSIZE + 2, deflt_fp))
    {
      if (strlen (deflt_buf) > _DEFLT_BUFSIZE)
        break;

      /* Trim trailing newline.  */
      size_t len = strlen (deflt_buf);
      if (len && deflt_buf[len - 1] == '\n')
        deflt_buf[len - 1] = '\0';

      /* Eat spaces.  */
      char *bufp = deflt_buf - 1;
      while (*++bufp == ' ') ;

      if ((*strcmpfunc)(bufp, cp, cplen) == 0)
        {
          bufp += cplen;

          /* Strip quotes.  */
          if ((deflt_flags & DC_STRIP_QUOTES) && *bufp)
            {
              /* Strip leading quote.  */
              if (*bufp == '"' || *bufp == '\'')
                {
                  char *bufp2 = bufp, *bufp3 = bufp;
                  while ((*bufp2++ = *++bufp3)) ;
                }

              /* Strip trailing quote.  */
              len = strlen (bufp);
              if (len && (bufp[len - 1] == '"' || bufp[len - 1] == '\''))
                bufp[len - 1] = '\0';
            }

          return bufp;
        }
    }

  return NULL;
}


int defcntl (int cmd, int newflags)
{
  int oldflags = deflt_flags;
  switch (cmd)
    {
    case DC_GETFLAGS:
      return oldflags;
    case DC_SETFLAGS:
      deflt_flags = newflags;
      return oldflags;
    default:
      return -1;
    }
}
