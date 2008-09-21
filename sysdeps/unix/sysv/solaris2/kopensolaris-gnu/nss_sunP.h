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

#ifndef _NSS_SUNP_H
#define _NSS_SUNP_H

#include <sys/types.h>
#include <nss/nsswitch.h>
#include "nss_common.h"

typedef struct
  {
	void *result;
	char *buffer;
	int buflen;
  } nss_XbyY_buf_t;

typedef int (*nss_str2ent_t)(const char *, int, void *, char *, int);

typedef union nss_XbyY_key
  {
	uid_t uid;
	gid_t gid;
	projid_t projid;
	const char *name;
	int number;
	struct
	  {
		int net;
		int type;
	  } netaddr;
	struct
	  {
		const char *addr;
		int len;
        int type;
	  } hostaddr;
	struct
	  {
		union
		  {
			const char *name;
            int port;
		  } serv;
        const char *proto;
	  } serv;
	void *ether;
	struct
	  {
		const char *name;
		const char *keytype;
	  } pkey;
	struct
	  {
		const char *name;
		int af_family;
		int flags;
	  } ipnode;
	void *attrp;
} nss_XbyY_key_t;

typedef int (*nss_key2str_t)(void *, size_t, nss_XbyY_key_t *, size_t *);

typedef struct nss_XbyY_args
  {
	nss_XbyY_buf_t buf;
	int stayopen;
	nss_str2ent_t str2ent;
	union nss_XbyY_key key;
	void *returnval;
	int erange;
	int h_errno;
	nss_status_t status;
	nss_key2str_t key2str;
	size_t returnlen;
  } nss_XbyY_args_t;

struct nss_getent_context
  {
    char getfuncname[30];
    char setfuncname[30];
    char endfuncname[30];
    db_lookup_function dblookup;

	service_user *nip;
	service_user *last_nip;
	service_user *startp;

    int stayopen;
    int stayopen_tmp;
  };

#define RESULT_TO_STATUS(res) \
	((res == 0) ? NSS_SUCCESS : (res == ENOENT) ? NSS_TRYAGAIN : NSS_ERROR)

enum nss_dbid
  {
	NSS_DBID_AUTH_ATTR,
	NSS_DBID_AUTOMOUNT,
	NSS_DBID_BOOTPARAMS,
	NSS_DBID_NETMASKS,
	NSS_DBID_PRINTERS,
	NSS_DBID_PROF_ATTR,
	NSS_DBID_PROJECT
  };

extern int __nss_dbname_to_dbid (const char *dbname);
extern const char * __nss_dbop_to_name (int dbid, int search_fnum);
extern db_lookup_function __nss_dbname_to_lookup (const char * dbname);

#endif /* _NSS_SUNP_H */
