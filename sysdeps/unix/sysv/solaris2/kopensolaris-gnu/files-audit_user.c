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

#include <auditP.h>

#define STRUCTURE	au_user_str_s
#define ENTNAME		auuser
#define DATABASE	"security/audit_user"
struct auuserent_data {};

#include "files-parse.c"
LINE_PARSER
(,
 STRING_FIELD (result->au_name, ISCOLON, 0);
 STRING_FIELD (result->au_always, ISCOLON, 0);
 STRING_FIELD (result->au_never, ISCOLON, 0);
 )

#include GENERIC

DB_LOOKUP (auusernam, 1 + strlen (name), (".%s", name),
	   {
	     if (! strcmp (name, result->au_name))
	       break;
	   }, const char *name)
