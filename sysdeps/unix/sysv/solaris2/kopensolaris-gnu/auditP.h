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

#ifndef _AUDITP_H
#define _AUDITP_H

#include <sys/types.h>

typedef uid_t au_id_t;
typedef pid_t au_asid_t;

typedef struct au_port_s
  {
	uint32_t at_major;
	uint32_t at_minor;
  } au_port_t;

typedef struct au_tid_addr64
  {
    au_port_t at_port;
	unsigned int at_type;
	unsigned int at_addr[4];
  } au_tid64_addr_t;

typedef struct au_mask
  {
	unsigned int am_success;
	unsigned int am_failure;
  } au_mask_t;

typedef struct auditinfo_addr64
  {
    au_id_t     ai_auid;
    au_mask_t   ai_mask;
    au_tid64_addr_t ai_termid;
    au_asid_t   ai_asid;
  } auditinfo64_addr_t;

typedef struct au_user_str_s
  {
	char *au_name;
	char *au_always;
	char *au_never;
  } au_user_str_t;

typedef struct _mac_label_impl m_label_t;
typedef m_label_t bslabel_t;

#define AU_NOAUDITID	((au_id_t)-2)

#endif /* _AUDITP_H */
