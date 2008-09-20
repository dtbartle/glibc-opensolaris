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

#ifndef _NSS_COMMON_H
#define _NSS_COMMON_H

#include <sys/types.h>
#include <stdint.h>
#include <synch.h> /* mutex_t */

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
	mutex_t lock;
  } nss_db_root_t;

#define NSS_DB_ROOT_INIT		{ 0, DEFAULTMUTEX }
#define DEFINE_NSS_DB_ROOT(name)	nss_db_root_t name = NSS_DB_ROOT_INIT

typedef struct
  {
	struct nss_getent_context *ctx;
	mutex_t lock;
  } nss_getent_t;

#define NSS_GETENT_INIT			{ 0, DEFAULTMUTEX }
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
	mutex_t *lock;
	void *buffer;
	size_t length;
  } nss_config_t;

__BEGIN_DECLS

extern nss_status_t nss_config (nss_config_t **, int);

extern nss_status_t nss_search (nss_db_root_t *, nss_db_initf_t,
	int search_fnum, void *search_args);
extern nss_status_t nss_getent (nss_db_root_t *, nss_db_initf_t,
	nss_getent_t *, void *getent_args);
extern void nss_setent (nss_db_root_t *, nss_db_initf_t, nss_getent_t *);
extern void nss_endent (nss_db_root_t *, nss_db_initf_t, nss_getent_t *);
extern void nss_delete (nss_db_root_t *);

extern nss_status_t nss_pack (void *, size_t, nss_db_root_t *,
	nss_db_initf_t, int, void *);
extern nss_status_t nss_pack_ent (void *, size_t, nss_db_root_t *,
	nss_db_initf_t, nss_getent_t *);
extern nss_status_t nss_unpack (void *, size_t, nss_db_root_t *,
	nss_db_initf_t, int, void *);
extern nss_status_t nss_unpack_ent (void *, size_t, nss_db_root_t *,
	nss_db_initf_t, nss_getent_t *, void *);

extern nss_status_t _nsc_search (nss_db_root_t *, nss_db_initf_t,
	int search_fnum, void *search_args);
extern nss_status_t _nsc_getent_u (nss_db_root_t *, nss_db_initf_t,
	 nss_getent_t *, void *getent_args);
extern nss_status_t _nsc_setent_u (nss_db_root_t *, nss_db_initf_t,
	nss_getent_t *);
extern nss_status_t _nsc_endent_u(nss_db_root_t *, nss_db_initf_t,
	    nss_getent_t *);

__END_DECLS

#endif /* _NSS_COMMON_H */
