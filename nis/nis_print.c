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

#include <time.h>
#include <rpcsvc/nis.h>
#include <rpcsvc/nislib.h>

static const char *
nis_nstype2str (const nstype type)
{
  switch (type)
    {
    case NIS:
      return "NIS";
    case SUNYP:
      return "SUNYP";
    case IVY:
      return "IVY";
    case DNS:
      return "DNS";
    case X500:
      return "X500";
    case DNANS:
      return "DNANS";
    case XCHS:
      return "XCHS";
    case CDS:
      return "CDS";
    default:
      return "UNKNOWN";
    }
}

static char *
nis_ttl2str (const u_long ttl)
{
  static char buf[64];
  unsigned long int time, s, m, h;

  time = ttl;

  h = time / (60 * 60);
  time %= (60 * 60);
  m = time / 60;
  time %= 60;
  s = time;
  snprintf (buf, 63, "%lu:%02lu:%02lu", h, m, s);

  return buf;
}

static char *
nis_flags2str (const u_long flags)
{
  static char buf[1024];

  snprintf (buf, 1023, "%lu", flags);

  return buf;
}

void
nis_print_rights (const u_long access)
{
  char result[17];
  u_long acc;
  int i;

  acc = access;			/* Parameter is const ! */
  result[i = 16] = '\0';
  while (i > 0)
    {
      i -= 4;
      result[i + 0] = (acc & NIS_READ_ACC) ? 'r' : '-';
      result[i + 1] = (acc & NIS_MODIFY_ACC) ? 'm' : '-';
      result[i + 2] = (acc & NIS_CREATE_ACC) ? 'c' : '-';
      result[i + 3] = (acc & NIS_DESTROY_ACC) ? 'd' : '-';

      acc >>= 8;
    }
  printf ("%s", result);
}

void
nis_print_directory (const directory_obj * dir)
{
  nis_server *sptr;
  unsigned int i;

  printf ("Name : '%s'\n", dir->do_name);
  printf ("Type : %s\n", nis_nstype2str (dir->do_type));
  sptr = dir->do_servers.do_servers_val;
  for (i = 0; i < dir->do_servers.do_servers_len; i++)
    {
      if (i == 0)
	printf ("Master Server :\n");
      else
	printf ("Replicate :\n");
      printf ("\tName       : %s\n", sptr->name);
      printf ("\tPublic Key : ");
      switch (sptr->key_type)
	{
	case NIS_PK_NONE:
	  printf ("None.\n");
	  break;
	case NIS_PK_DH:
	  printf ("DH.\n");
	  break;
	case NIS_PK_RSA:
	  printf ("RSA.\n");
	  break;
	case NIS_PK_KERB:
	  printf ("Kerberous.\n");
	  break;
	default:
	  printf ("Unknown.\n");
	  break;
	}

      if (sptr->ep.ep_len != 0)
	{
	  unsigned int j;

	  endpoint *ptr;
	  ptr = sptr->ep.ep_val;
	  printf ("\tUniversal addresses (%u)\n", sptr->ep.ep_len);
	  for (j = 0; j < sptr->ep.ep_len; j++)
	    {
	      printf ("\t[%d] - ", j + 1);
	      if (ptr->proto != NULL && strlen (ptr->proto) > 0)
		printf ("%s, ", ptr->proto);
	      else
		printf ("-, ");
	      if (ptr->family != NULL && strlen (ptr->family) > 0)
		printf ("%s, ", ptr->family);
	      else
		printf ("-, ");
	      if (ptr->uaddr != NULL && strlen (ptr->uaddr) > 0)
		printf ("%s\n", ptr->uaddr);
	      else
		printf ("-\n");
	      ptr++;
	    }
	}
      sptr++;
    }

  printf ("Time to live : %s\n", nis_ttl2str (dir->do_ttl));
  if (dir->do_armask.do_armask_len != 0)
    {
      oar_mask *ptr;

      ptr = dir->do_armask.do_armask_val;
      for (i = 0; i < dir->do_armask.do_armask_len; i++)
	{
	  printf ("Default Access rights: ");
	  nis_print_rights (ptr->oa_rights);
	  printf ("\nDirect Type : %d\n", ptr->oa_otype);
	  ptr++;
	}
    }
}

void
nis_print_group (const group_obj * obj)
{
  unsigned int i;

  printf ("Group Flags :");
  if (obj->gr_flags)
    printf ("0x%08lX", obj->gr_flags);
  printf ("\nGroup Members :\n");

  for (i = 0; i < obj->gr_members.gr_members_len; i++)
    printf ("\t%s\n", obj->gr_members.gr_members_val[i]);
}

void
nis_print_table (const table_obj * obj)
{
  unsigned int i;

  printf ("Table Type          : %s\n", obj->ta_type);
  printf ("Number of Columns   : %d\n", obj->ta_maxcol);
  printf ("Character Separator : %c\n", obj->ta_sep);
  printf ("Search Path         : %s\n", obj->ta_path);
  printf ("Columns             :\n");
  for (i = 0; i < obj->ta_cols.ta_cols_len; i++)
    {
      printf ("\t[%d]\tName          : %s\n", i,
	      obj->ta_cols.ta_cols_val[i].tc_name);
      printf ("\t\tAttributes    : %s\n",
	      nis_flags2str (obj->ta_cols.ta_cols_val[i].tc_flags));
      printf ("\t\tAccess Rights : ");
      nis_print_rights (obj->ta_cols.ta_cols_val[i].tc_rights);
      printf ("\n");
    }
}

void
nis_print_link (const link_obj * obj)
{
  printf ("Type : %d\n", obj->li_rtype);
  printf ("Name : %s\n", obj->li_name);
  printf ("Attributes : %d\n", obj->li_attrs.li_attrs_len);
}

void 
nis_print_entry (const entry_obj * obj)
{
  unsigned int i;

  printf ("\tEntry data of type %s\n", obj->en_type);
  for (i = 0; i < obj->en_cols.en_cols_len; i++)
    {
      printf ("\t[%u] - [%u bytes] ", i,
	      obj->en_cols.en_cols_val[i].ec_value.ec_value_len);
      if ((obj->en_cols.en_cols_val[i].ec_flags & EN_CRYPT) == EN_CRYPT)
	printf ("Encrypted data\n");
      else if ((obj->en_cols.en_cols_val[i].ec_flags & EN_BINARY) == EN_BINARY)
	printf ("Binary data\n");
      else
	printf ("%s\n", obj->en_cols.en_cols_val[i].ec_value.ec_value_val);
    }
}

void
nis_print_object (const nis_object * obj)
{
  printf ("Object Name   : %s\n", obj->zo_name);
  printf ("Directory     : %s\n", obj->zo_domain);
  printf ("Owner         : %s\n", obj->zo_owner);
  printf ("Group         : %s\n", obj->zo_group);
  printf ("Access Rights : ");
  nis_print_rights (obj->zo_access);
  printf ("\nTime to Live  : %lu (seconds)\n", obj->zo_ttl);
  printf ("Creation Time : %s", ctime (&obj->zo_oid.ctime));
  printf ("Mod. Time     : %s", ctime (&obj->zo_oid.mtime));
  printf ("Object Type   : ");
  switch (obj->zo_data.zo_type)
    {
    case BOGUS_OBJ:
      printf ("BOGUS OBJECT\n");
      break;
    case NO_OBJ:
      printf ("NO OBJECT\n");
      break;
    case DIRECTORY_OBJ:
      printf ("DIRECTORY\n");
      nis_print_directory (&obj->zo_data.objdata_u.di_data);
      break;
    case GROUP_OBJ:
      printf ("GROUP\n");
      nis_print_group (&obj->zo_data.objdata_u.gr_data);
      break;
    case TABLE_OBJ:
      printf ("TABLE\n");
      nis_print_table (&obj->zo_data.objdata_u.ta_data);
      break;
    case ENTRY_OBJ:
      printf ("ENTRY\n");
      nis_print_entry (&obj->zo_data.objdata_u.en_data);
      break;
    case LINK_OBJ:
      printf ("LINK\n");
      nis_print_link (&obj->zo_data.objdata_u.li_data);
      break;
    case PRIVATE_OBJ:
      printf ("PRIVATE\n");
      printf ("    Data Length = %u\n",
	      obj->zo_data.objdata_u.po_data.po_data_len);
      break;
    default:
      printf ("(Unknown object)\n");
      break;
    }
}

void
nis_print_result (const nis_result * res)
{
  unsigned int i;

  printf ("Status            : %s\n", nis_sperrno (res->status));
  printf ("Number of objects : %u\n", res->objects.objects_len);

  for (i = 0; i < res->objects.objects_len; i++)
    {
      printf ("Object #%d:\n", i);
      nis_print_object (&res->objects.objects_val[i]);
    }
}
