/* Copyright (c) 1997 Free Software Foundation, Inc.

   This file is part of the GNU C Library.
   Contributed by Thorsten Kukuk <kukuk@vt.uni-paderborn.de>, 1997.
   
   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.
   
   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.
   
   You should have received a copy of the GNU Library General Public
   License along with the GNU C Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

#include <errno.h>
#include <syslog.h>
#include <rpcsvc/nis.h>
#include <rpcsvc/nislib.h>


static const char *nis_errlist[] = 
{
  "Success",
  "Probable success",
  "Not found",
  "Probably not found",
  "Cache expired",
  "NIS+ servers unreachable",
  "Unknown object",
  "Server busy, try again",
  "Generic system error",
  "First/Next chain broken",
  "Permission denied",
  "Not owner",
  "Name not served by this server",
  "Server out of memory",
  "Object with same name exists",
  "Not master server for this domain",
  "Invalid Object for operation",
  "Malformed Name, or illegal name",
  "Unable to create callback",
  "Results Sent to callback proc",
  "Not Found, no such name",
  "Name/entry isn't unique",
  "Modification failed",
  "Database for table does not exist",
  "Entry/Table type mismatch",
  "Link Points to illegal name",
  "Partial Success",
  "Too Many Attributes",
  "Error in RPC subsystem",
  "Missing or malformed attribute",
  "Named object is not searchable",
  "Error while talking to callback proc",
  "Non NIS+ namespace encountered",
  "Illegal object type for operation",
  "Passed object is not the same object on server",
  "Modify operation failed",
  "Query illegal for named table",
  "Attempt to remove a non-empty table",
  "Error in accessing NIS+ cold start file.  Is NIS+ installed?",
  "Full resync required for directory",
  "NIS+ operation failed",
  "NIS+ service is unavailable or not installed",
  "Yes, 42 is the meaning of life",
  "Unable to authenticate NIS+ server",
  "Unable to authenticate NIS+ client",
  "No file space on server",
  "Unable to create process on server",
  "Master server busy, full dump rescheduled."
};

char *
nis_sperrno (const nis_error status)
{
  if (status >= (sizeof (nis_errlist)/sizeof (nis_errlist[0])))
    return "?";
  else 
    return nis_errlist[status];
}

void 
nis_perror (const nis_error status, const char *label)
{
  fprintf(stderr, "%s: %s\n", label, nis_sperrno(status));
}

void 
nis_lerror (const nis_error status, const char *label)
{
  syslog(LOG_ERR, "%s: %s", label, nis_sperrno (status));
}

char *
nis_sperror_r (const nis_error status, const char *label,
	       char *buffer, size_t buflen)
{
  char *cptr;

  cptr = nis_sperrno (status);
 
  if ((strlen (cptr) + strlen (label) + 3) > buflen)
    {
      errno = ERANGE;
      return NULL;
    }
  
    sprintf(buffer, "%s: %s", label, cptr);

    return buffer;
}

char *
nis_sperror (const nis_error status, const char *label)
{
  static char buffer [NIS_MAXNAMELEN +1];

  return nis_sperror_r (status, label, buffer, sizeof (buffer));
}

