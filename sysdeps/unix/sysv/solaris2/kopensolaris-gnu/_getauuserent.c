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

#include <auditP.h>

#define LOOKUP_TYPE	au_user_str_t
#define SETFUNC_NAME	setauuser
#define	GETFUNC_NAME	getauuserent
#define	ENDFUNC_NAME	endauuser
#define DATABASE_NAME	passwd
#define BUFLEN		NSS_BUFLEN_AUDITUSER

#include <nss/getXXent_r.c>

extern int getauuserent_r (au_user_str_t *, char *, size_t, au_user_str_t **);


au_user_str_t * _getauuserent (au_user_str_t *psbuf, char *buf, int buflen, int *errnop)
{
  au_user_str_t *psbufp;
  int errval = getauuserent_r (psbuf, buf, buflen, &psbufp);
  if (errval && errnop)
    *errnop = errval;

  return errval ? NULL : psbuf;
}

strong_alias (setauuser, _setauuser)
strong_alias (endauuser, _endauuser)
