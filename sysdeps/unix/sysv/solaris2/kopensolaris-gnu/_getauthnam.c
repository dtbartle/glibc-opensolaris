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

#include <auth_attrP.h>

#define LOOKUP_TYPE	authstr_t
#define FUNCTION_NAME	getauthnam
#define DATABASE_NAME	passwd
#define ADD_PARAMS	const char *name
#define ADD_VARIABLES	name
#define BUFLEN		NSS_BUFLEN_AUTHATTR

#include <nss/getXXbyYY_r.c>

extern int getauthnam_r (const char *, authstr_t *, char *, size_t,
    authstr_t **);


authstr_t * _getauthnam (const char *name, authstr_t *psbuf, char *buf,
      int buflen, int *errnop)
{
  authstr_t *psbufp;
  int errval = getauthnam_r (name, psbuf, buf, buflen, &psbufp);
  if (errval && errnop)
    *errnop = errval;

  return errval ? NULL : psbuf;
}
