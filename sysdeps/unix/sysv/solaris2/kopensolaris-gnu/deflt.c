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

/* XXX: OpenSolaris uses a per-thread buffer.  */

_DEFLT_INIT

int defopen (char *fn)
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


char * defread (char *cp)
{
  if (_DEFLT (fp) == NULL)
      return NULL;

  /* Rewind if needed.  */
  if ((_DEFLT (flags) & DC_NOREWIND) == 0)
    rewind (_DEFLT (fp));

  size_t cplen = strlen (cp);
  int (*strcmpfunc)(const char *, const char *, size_t) =
      (_DEFLT (flags) & DC_CASE) ? strncmp : strncasecmp;
  while (fgets (_DEFLT (buf), _DEFLT_BUFSIZE, _DEFLT (fp)))
    {
      /* Trim trailing newline.  */
      size_t len = strlen (_DEFLT (buf));
      if (len && _DEFLT (buf)[len - 1] == '\n')
        _DEFLT (buf)[len - 1] = '\0';

      /* Eat spaces.  */
      char *bufp = _DEFLT (buf) - 1;
      while (*++bufp == ' ') ;

      if ((*strcmpfunc)(bufp, cp, cplen) == 0)
        {
          bufp += cplen;

          /* Strip quotes.  */
          if ((_DEFLT (flags) & DC_STRIP_QUOTES) && *bufp)
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


// TODO
#if 0
int defcntl (int cmd, int newflags)
{
}
#endif
