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

#include <exec_attrP.h>

#define LOOKUP_TYPE	execstr_t
#define SETFUNC_NAME	setexecattr
#define	GETFUNC_NAME	getexecattr
#define	ENDFUNC_NAME	endexecattr
#define DATABASE_NAME	prof_attr
#define BUFLEN		NSS_BUFLEN_EXECATTR

#include <nss/getXXent_r.c>

extern int getexecattr_r (execstr_t *, char *, size_t, execstr_t **);


execstr_t * _getexecattr (execstr_t *esbuf, char *buf, int buflen, int *errnop)
{
  execstr_t *esbufp;
  int errval = getexecattr_r (esbuf, buf, buflen, &esbufp);
  if (errval && errnop)
    *errnop = errval;

  return errval ? NULL : esbuf;
}

strong_alias (setexecattr, _setexecattr)
strong_alias (endexecattr, _endexecattr)
