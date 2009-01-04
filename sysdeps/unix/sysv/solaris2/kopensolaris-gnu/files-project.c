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

#include <projectP.h>

#define STRUCTURE	project
#define ENTNAME		proj
#define DATABASE	"project"
struct projent_data {};

#include "files-parse.c"
// TODO: need to split out pj_users and pj_groups
LINE_PARSER
(,
 STRING_FIELD (result->pj_name, ISCOLON, 0);
 INT_FIELD (result->pj_projid, ISCOLON, 0, 10, (projid_t))
 STRING_FIELD (result->pj_comment, ISCOLON, 0);
 STRING_FIELD (result->pj_users, ISCOLON, 0);
 STRING_FIELD (result->pj_groups, ISCOLON, 0);
 STRING_FIELD (result->pj_attr, ISCOLON, 0);
 )

#include GENERIC

DB_LOOKUP (projnam, 1 + strlen (name), (".%s", name),
	   {
	     if (! strcmp (name, result->pj_name))
	       break;
	   }, const char *name)
