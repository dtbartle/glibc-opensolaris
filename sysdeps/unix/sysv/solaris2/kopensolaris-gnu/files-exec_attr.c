/* User file parser in nss_files module.
   Copyright (C) 1996, 1997, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

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

#define STRUCTURE	execstr_s
#define ENTNAME		execattr
#define DATABASE	"security/exec_attr"
struct execattrent_data {};

#include "files-parse.c"
LINE_PARSER
(,
 STRING_FIELD (result->name, ISCOLON, 0);
 STRING_FIELD (result->policy, ISCOLON, 0);
 STRING_FIELD (result->type, ISCOLON, 0);
 STRING_FIELD (result->res1, ISCOLON, 0);
 STRING_FIELD (result->res2, ISCOLON, 0);
 STRING_FIELD (result->id, ISCOLON, 0);
 STRING_FIELD (result->attr, ISCOLON, 0);
 result->next = NULL;
 )

#include GENERIC

DB_LOOKUP (execnam, 1 + strlen (name), (".%s", name),
	   {
	     if (! strcmp (name, result->name))
	       break;
	   }, const char *name)
