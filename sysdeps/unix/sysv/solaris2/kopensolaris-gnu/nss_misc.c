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

#include <nss_sunP.h>
#include <string.h>

int __nss_dbname_to_dbid (const char *dbname)
{
  if (strcmp (dbname, "auth_attr") == 0)
    return NSS_DBID_AUTH_ATTR;
  if (strcmp (dbname, "automount") == 0)
    return NSS_DBID_AUTOMOUNT;
  if (strcmp (dbname, "bootparams") == 0)
    return NSS_DBID_BOOTPARAMS;
  if (strcmp (dbname, "netmasks") == 0)
    return NSS_DBID_NETMASKS;
  if (strcmp (dbname, "printers") == 0)
    return NSS_DBID_PRINTERS;
  if (strcmp (dbname, "prof_attr") == 0)
    return NSS_DBID_PROF_ATTR;
  if (strcmp (dbname, "project") == 0)
    return NSS_DBID_PROJECT;

  return -1;
}


const char * __nss_dbop_to_name (int dbid, int search_fnum)
{
  // TODO
  switch (dbid)
    {
    case NSS_DBID_AUTH_ATTR:
    case NSS_DBID_AUTOMOUNT:
    case NSS_DBID_BOOTPARAMS:
    case NSS_DBID_NETMASKS:
    case NSS_DBID_PRINTERS:
    case NSS_DBID_PROF_ATTR:
    case NSS_DBID_PROJECT:
      break;
    }

  return NULL;
}


db_lookup_function __nss_dbname_to_lookup (const char *dbname)
{
  extern int internal_function __nss_auth_attr_lookup (service_user **,
      const char *, void **);
  extern int internal_function __nss_automount_lookup (service_user **,
      const char *, void **);
  extern int internal_function __nss_bootparams_lookup (service_user **,
      const char *, void **);
  extern int internal_function __nss_netmasks_lookup (service_user **,
      const char *, void **);
  extern int internal_function __nss_printers_lookup (service_user **,
      const char *, void **);
  extern int internal_function __nss_prof_attr_lookup (service_user **,
      const char *, void **);
  extern int internal_function __nss_project_lookup (service_user **,
      const char *, void **);

  int dbid = __nss_dbname_to_dbid (dbname);
  if (dbid == -1)
    return NULL;

  switch (dbid)
    {
    case NSS_DBID_AUTH_ATTR:
      return __nss_auth_attr_lookup;
    case NSS_DBID_AUTOMOUNT:
      return __nss_automount_lookup;
    case NSS_DBID_BOOTPARAMS:
      return __nss_bootparams_lookup;
    case NSS_DBID_NETMASKS:
      return __nss_netmasks_lookup;
    case NSS_DBID_PRINTERS:
      return __nss_printers_lookup;
    case NSS_DBID_PROF_ATTR:
      return __nss_prof_attr_lookup;
    case NSS_DBID_PROJECT:
      return __nss_project_lookup;
    }

  return NULL;
}
