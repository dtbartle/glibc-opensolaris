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

#ifndef _NSSP_H
#define _NSSP_H

#include <sys/types.h>
#include <nss/nsswitch.h>
#include <stdint.h>
#include <pthread.h>

typedef enum
  {
	NSS_SUCCESS = 0,
	NSS_NOTFOUND = 1,
	NSS_UNAVAIL = 2,
	NSS_TRYAGAIN = 3,
	NSS_NISSERVDNS_TRYAGAIN = 4,
	NSS_TRYLOCAL = 5,
	NSS_ERROR = 6,
	NSS_ALTRETRY = 7,
	NSS_ALTRESET = 8,
	NSS_NSCD_PRIV = 9
  } nss_status_t;

struct nss_backend;

typedef nss_status_t (*nss_backend_op_t) (struct nss_backend *, void *);

typedef struct nss_backend
  {
	nss_backend_op_t *ops;
	int n_ops;
  } nss_backend_t;

typedef int nss_dbop_t;

#define NSS_DBOP_DESTRUCTOR	0
#define NSS_DBOP_ENDENT		1
#define NSS_DBOP_SETENT		2
#define NSS_DBOP_GETENT		3
#define NSS_DBOP_next_iter	(NSS_DBOP_GETENT + 1)
#define NSS_DBOP_next_noiter	(NSS_DBOP_DESTRUCTOR + 1)
#define NSS_DBOP_next_ipv6_iter	(NSS_DBOP_GETENT + 3)

#define NSS_LOOKUP_DBOP(instp, n) \
	(((n) >= 0 && (n) < (instp)->n_ops) ? (instp)->ops[n] : 0)

#define NSS_INVOKE_DBOP(instp, n, argp) \
	(((n) >= 0 && (n) < (instp)->n_ops && (instp)->ops[n] != 0) \
	? (*(instp)->ops[n])(instp, argp) : NSS_UNAVAIL)

typedef nss_backend_t * (*nss_backend_constr_t) (const char *db_name,
	const char *src_name, const char *cfg_args);

typedef struct nss_backend_finder
  {
	nss_backend_constr_t (*lookup) (void *lkp_priv, const char *,
		const char *, void **del_privp);
	void (*delete) (void *del_priv, nss_backend_constr_t);
	struct nss_backend_finder *next;
	void *lookup_priv;
  } nss_backend_finder_t;

extern nss_backend_finder_t *nss_default_finders;

enum nss_dbp_flags
  {
	NSS_USE_DEFAULT_CONFIG  = 0x1
  };

typedef struct nss_db_params
  {
	const char *name;
	const char *config_name;
	const char *default_config;
	unsigned max_active_per_src;
	unsigned max_dormant_per_src;
	enum nss_dbp_flags flags;
	nss_backend_finder_t *finders;
	void *private;
	void (*cleanup) (struct nss_db_params *);
  } nss_db_params_t;

typedef void (*nss_db_initf_t) (nss_db_params_t *);

typedef struct nss_dbd {
	uint32_t o_name;
	uint32_t o_config_name;
	uint32_t o_default_config;
	uint32_t flags;
  } nss_dbd_t;

struct nss_db_state;
struct nss_getent_context;

typedef struct nss_db_root
  {
	struct nss_db_state *s;
	pthread_mutex_t lock;
  } nss_db_root_t;

#define NSS_DB_ROOT_INIT		{ 0, PTHREAD_MUTEX_INITIALIZER }
#define DEFINE_NSS_DB_ROOT(name)	nss_db_root_t name = NSS_DB_ROOT_INIT

typedef struct
  {
	struct nss_getent_context *ctx;
	pthread_mutex_t lock;
  } nss_getent_t;

#define NSS_GETENT_INIT			{ 0, PTHREAD_MUTEX_INITIALIZER }
#define DEFINE_NSS_GETENT(name)		nss_getent_t name = NSS_GETENT_INIT

typedef enum
  {
	NSS_CONFIG_GET,
	NSS_CONFIG_PUT,
	NSS_CONFIG_ADD,
	NSS_CONFIG_DELETE,
	NSS_CONFIG_LIST
  } nss_config_op_t;

typedef struct nss_config
  {
	char *name;
	nss_config_op_t cop;
	void *lock;
	void *buffer;
	size_t length;
  } nss_config_t;

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
    db_lookup_function dblookupfunc;

	service_user *nip;
	service_user *last_nip;
	service_user *startp;

    int stayopen;
    int stayopen_tmp;
  };

#define NSS_STR_PARSE_SUCCESS	0
#define NSS_STR_PARSE_PARSE	1
#define NSS_STR_PARSE_ERANGE	2

typedef enum nss_status (*lookup_function) (void *, char *, size_t, int *);

struct nss_db_state
  {
	bool startp_initialized;
	service_user *startp;
	lookup_function start_fct;

    db_lookup_function dblookupfunc;
    const char **dbtable;
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
	NSS_DBID_PROJECT,
	_NSS_DBID_MAX = NSS_DBID_PROJECT
  };

#define _NSS_DBENTRY_MAX	6

extern int __nss_get_dbid (const char *dbname);
extern const char ** __nss_get_dbtable (int dbid);
extern db_lookup_function __nss_get_dblookupfunc (int dbid);


#endif /* _NSSP_H */
