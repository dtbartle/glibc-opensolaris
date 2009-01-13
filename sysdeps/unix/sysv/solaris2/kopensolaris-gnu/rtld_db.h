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

#ifndef _RTLD_DB_H
#define _RTLD_DB_H

#include <sys/types.h>
#include <features.h>
#include <proc_service.h>
#include <sys/link.h>
#include <dlfcn.h>

#define RD_VERSION1	1
#define RD_VERSION2	2
#define RD_VERSION3	3
#define RD_VERSION4	4
#define RD_VERSION	RD_VERSION4

typedef enum
  {
	RD_ERR,
	RD_OK,
	RD_NOCAPAB,
	RD_DBERR,
	RD_NOBASE,
	RD_NODYNAM,
	RD_NOMAPS
  } rd_err_e;

typedef struct rd_agent rd_agent_t;

typedef struct rd_loadobj
  {
	psaddr_t rl_nameaddr;
	unsigned int rl_flags;
	psaddr_t rl_base;
	psaddr_t rl_data_base;
	Lmid_t rl_lmident;
	psaddr_t rl_refnameaddr;
	psaddr_t rl_plt_base;
	unsigned int rl_plt_size;
	psaddr_t rl_bend;
	psaddr_t rl_padstart;
	psaddr_t rl_padend;
	psaddr_t rl_dynamic;
	unsigned long rl_tlsmodid;
  } rd_loadobj_t;

/* r_flags values.  */
#define RD_FLG_MEM_OBJECT	0x0001

typedef int rl_iter_f (const rd_loadobj_t *, void *);

typedef enum
  {
	RD_NOTIFY_BPT,
	RD_NOTIFY_AUTOBPT,
	RD_NOTIFY_SYSCALL
  } rd_notify_e;

typedef struct rd_notify
  {
	rd_notify_e type;
	union
	  {
		psaddr_t bptaddr;
		long syscallno;
	  } u;
  } rd_notify_t;

typedef enum
  {
	RD_NOSTATE = 0,
	RD_CONSISTENT,
	RD_ADD,
	RD_DELETE
  } rd_state_e;

typedef struct rd_event_msg
  {
	rd_event_e type;
	union
	  {
		rd_state_e state;
	  } u;
  } rd_event_msg_t;

typedef enum
  {
	RD_RESOLVE_NONE,
	RD_RESOLVE_STEP,
	RD_RESOLVE_TARGET,
	RD_RESOLVE_TARGET_STEP
  } rd_skip_e;

typedef struct rd_plt_info
  {
	rd_skip_e pi_skip_method;
	long pi_nstep;
	psaddr_t pi_target;
	psaddr_t pi_baddr;
	unsigned int pi_flags;
  } rd_plt_info_t;

/* pi_flags values.  */
#define RD_FLG_PI_PLTBOUND	0x01

/* rd_ctl commands.  */
#define RD_CTL_SET_HELPPATH	0x01

__BEGIN_DECLS

extern void rd_delete (rd_agent_t *);
extern char * rd_errstr (rd_err_e);
extern rd_err_e rd_event_addr (rd_agent_t *, rd_event_e, rd_notify_t *);
extern rd_err_e rd_event_enable (rd_agent_t *, int);
extern rd_err_e rd_event_getmsg (rd_agent_t *, rd_event_msg_t *);
extern rd_err_e rd_init (int);
extern rd_err_e rd_ctl (int, void *);
extern rd_err_e rd_loadobj_iter (rd_agent_t *, rl_iter_f *, void *);
extern void rd_log (const int);
extern rd_agent_t * rd_new (struct ps_prochandle *);
extern rd_err_e rd_objpad_enable(struct rd_agent *, size_t);
extern rd_err_e rd_plt_resolution (rd_agent_t *, psaddr_t, lwpid_t, psaddr_t,
    rd_plt_info_t *);
extern rd_err_e rd_get_dyns (rd_agent_t *, psaddr_t, void **, size_t *);
extern rd_err_e rd_reset (struct rd_agent *);

__END_DECLS

#endif /* _RTLD_DB_H */
