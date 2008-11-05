/* Copyright (C) 1991,1996-1999,2001,2004,2008 Free Software Foundation, Inc.
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

/* These are a collection of simple functions that OpenSolaris' libnsl.so
   exports.  */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>


char * _strdup_null (char *str)
{
  return strdup (str ?: "");
}


char * _escape (char *str, char *escape)
{
  size_t len = strlen (str) + 1;
  for (size_t i = 0; i < strlen (str); i++)
    {
      if (strchr (escape, str[i]))
        len++;
    }

  char *ret = malloc (len);
  if (!ret)
    return NULL;

  char *retp = ret;
  for (size_t i = 0; i < strlen (str); i++)
    {
      if (strchr (escape, str[i]))
        *retp++ = '\\';
      *retp++ = str[i];
    }
  *retp = '\0';

  return ret;
}


char * _unescape (char *str, char *escape)
{
  char *ret = malloc (strlen (str) + 1);
  if (!ret)
    return NULL;

  char *retp = ret;
  for (size_t i = 0; i < strlen (str); i++)
    {
      if (str[i] == '\\' && str[i + 1] && strchr (escape, str[i + 1]))
        *retp++ = str[++i];
      else
        *retp++ = str[i];
    }
  *retp = '\0';

  return ret;
}


/* Return a pointer to the first non-escaped char or NULL if none exists.  */
char * _strpbrk_escape (char *str, char *brkset)
{
  for (size_t i = 0; i < strlen (str); i++)
    {
      if (strchr (brkset, str[i]) && (i == 0 || str[i - 1] != '\\'))
        return &str[i];
    }

  return NULL;
}


/* strtok_r except escaped chars are ignored.  */
_strtok_escape (char *s, const char *delim, char **save_ptr)
{
  char *token;

  if (s == NULL)
    s = *save_ptr;

  /* Scan leading delimiters.  */
  s += strspn (s, delim);
  if (*s == '\0')
    {
      *save_ptr = s;
      return NULL;
    }

  /* Find the end of the token.  */
  token = s;
  s = _strpbrk_escape (token, delim);
  if (s == NULL)
    /* This token finishes the string.  */
    *save_ptr = __rawmemchr (token, '\0');
  else
    {
      /* Terminate the token and make *SAVE_PTR point past it.  */
      *s = '\0';
      *save_ptr = s + 1;
    }
  return token;
}
