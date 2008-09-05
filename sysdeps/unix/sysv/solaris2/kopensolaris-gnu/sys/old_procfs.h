/* Declarations of old procfs structures.
   Copyright (C) 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

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

#ifndef _SYS_OLD_PROCFS_H
#define _SYS_OLD_PROCFS_H	1

#include <sys/procfs_isa.h>
#include <sys/types.h>
#include <sys/procset.h>
#include <sys/ucontext.h>
#include <sys/signal.h>
#include <sys/fault.h>

#define	PIOC		('q'<<8)
#define	PIOCSTATUS	(PIOC|1)
#define	PIOCSTOP	(PIOC|2)
#define	PIOCWSTOP	(PIOC|3)
#define	PIOCRUN		(PIOC|4)
#define	PIOCGTRACE	(PIOC|5)
#define	PIOCSTRACE	(PIOC|6)
#define	PIOCSSIG	(PIOC|7)
#define	PIOCKILL	(PIOC|8)
#define	PIOCUNKILL	(PIOC|9)
#define	PIOCGHOLD	(PIOC|10)
#define	PIOCSHOLD	(PIOC|11)
#define	PIOCMAXSIG	(PIOC|12)
#define	PIOCACTION	(PIOC|13)
#define	PIOCGFAULT	(PIOC|14)
#define	PIOCSFAULT	(PIOC|15)
#define	PIOCCFAULT	(PIOC|16)
#define	PIOCGENTRY	(PIOC|17)
#define	PIOCSENTRY	(PIOC|18)
#define	PIOCGEXIT	(PIOC|19)
#define	PIOCSEXIT	(PIOC|20)
#define	PIOCSFORK	(PIOC|21)
#define	PIOCRFORK	(PIOC|22)
#define	PIOCSRLC	(PIOC|23)
#define	PIOCRRLC	(PIOC|24)
#define	PIOCGREG	(PIOC|25)
#define	PIOCSREG	(PIOC|26)
#define	PIOCGFPREG	(PIOC|27)
#define	PIOCSFPREG	(PIOC|28)
#define	PIOCNICE	(PIOC|29)
#define	PIOCPSINFO	(PIOC|30)
#define	PIOCNMAP	(PIOC|31)
#define	PIOCMAP		(PIOC|32)
#define	PIOCOPENM	(PIOC|33)
#define	PIOCCRED	(PIOC|34)
#define	PIOCGROUPS	(PIOC|35)
#define	PIOCGETPR	(PIOC|36)
#define	PIOCGETU	(PIOC|37)
#define	PIOCSET		(PIOC|38)
#define	PIOCRESET	(PIOC|39)
#define	PIOCUSAGE	(PIOC|43)
#define	PIOCOPENPD	(PIOC|44)
#define	PIOCLWPIDS	(PIOC|45)
#define	PIOCOPENLWP	(PIOC|46)
#define	PIOCLSTATUS	(PIOC|47)
#define	PIOCLUSAGE	(PIOC|48)
#define	PIOCNAUXV	(PIOC|49)
#define	PIOCAUXV	(PIOC|50)
#define	PIOCGXREGSIZE	(PIOC|51)
#define	PIOCGXREG	(PIOC|52)
#define	PIOCSXREG	(PIOC|53)

#define	PIOCNLDT	(PIOC|103)
#define	PIOCLDT		(PIOC|104)

#define PRCLSZ		8
#define PRSYSARGS	8

typedef struct prstatus
  {
	int pr_flags;
	short pr_why;
	short pr_what;
	siginfo_t pr_info;
	short pr_cursig;
	unsigned short pr_nlwp;
	sigset_t pr_sigpend;
	sigset_t pr_sighold;
	struct sigaltstack pr_altstack;
	struct sigaction pr_action;
	pid_t pr_pid;
	pid_t pr_ppid;
	pid_t pr_pgrp;
	pid_t pr_sid;
	struct timespec pr_utime;
	struct timespec pr_stime;
	struct timespec pr_cutime;
	struct timespec pr_cstime;
	char pr_clname[PRCLSZ];
	short pr_syscall;
	short pr_nsysarg;
	long pr_sysarg[PRSYSARGS];
	id_t pr_who;
	sigset_t pr_lwppend;
	struct ucontext *pr_oldcontext;
	caddr_t pr_brkbase;
	size_t pr_brksize;
	caddr_t pr_stkbase;
	size_t pr_stksize;
	short pr_processor;
	short pr_bind;
	long pr_instr;
	prgregset_t pr_reg;
  } prstatus_t;

#define	PR_STOPPED	0x0001
#define	PR_ISTOP	0x0002
#define	PR_DSTOP	0x0004
#define	PR_ASLEEP	0x0008
#define	PR_FORK		0x0010
#define	PR_RLC		0x0020
#define	PR_PTRACE	0x0040
#define	PR_PCINVAL	0x0080
#define	PR_ISSYS	0x0100
#define	PR_STEP		0x0200
#define	PR_KLC		0x0400
#define	PR_ASYNC	0x0800
#define	PR_PCOMPAT	0x1000
#define	PR_MSACCT	0x2000
#define	PR_BPTADJ	0x4000
#define	PR_ASLWP	0x8000

#define	PR_REQUESTED	1
#define	PR_SIGNALLED	2
#define	PR_SYSENTRY	3
#define	PR_SYSEXIT	4
#define	PR_JOBCONTROL	5
#define	PR_FAULTED	6
#define	PR_SUSPENDED	7
#define	PR_CHECKPOINT	8

#define	PRFNSZ		16
#define	PRARGSZ		80

typedef struct prpsinfo
  {
	char pr_state;
	char pr_sname;
	char pr_zomb;
	char pr_nice;
	unsigned int pr_flag;
	uid_t pr_uid;
	gid_t pr_gid;
	pid_t pr_pid;
	pid_t pr_ppid;
	pid_t pr_pgrp;
	pid_t pr_sid;
	caddr_t pr_addr;
	size_t pr_size;
	size_t pr_rssize;
	caddr_t pr_wchan;
	struct timespec pr_start;
	struct timespec pr_time;
	int pr_pri;
	char pr_oldpri;
	char pr_cpu;
	o_dev_t pr_ottydev;
	dev_t pr_lttydev;
	char pr_clname[PRCLSZ];
	char pr_fname[PRFNSZ];
	char pr_psargs[PRARGSZ];
	short pr_syscall;
	short pr_fill;
	struct timespec pr_ctime;
	size_t pr_bysize;
	size_t pr_byrssize;
	int pr_argc;
	char	**pr_argv;
	char	**pr_envp;
	int pr_wstat;
	unsigned short pr_pctcpu;
	unsigned short pr_pctmem;
	uid_t pr_euid;
	gid_t pr_egid;
	id_t pr_aslwpid;
	char pr_dmodel;
	char pr_pad[3];
	int pr_filler[6];
  } prpsinfo_t;

typedef struct prrun
  {
	int pr_flags;
	sigset_t pr_trace;
	sigset_t pr_sighold;
	fltset_t pr_fault;
	caddr_t pr_vaddr;
	int pr_filler[8];
  } prrun_t;

#define	PRCSIG		0x001
#define	PRCFAULT	0x002
#define	PRSTRACE	0x004
#define	PRSHOLD		0x008
#define	PRSFAULT	0x010
#define	PRSVADDR	0x020
#define	PRSTEP		0x040
#define	PRSABORT	0x080
#define	PRSTOP		0x100

typedef struct prmap
  {
	caddr_t pr_vaddr;
	size_t pr_size;
	off_t pr_off;
	unsigned int pr_mflags;
	unsigned int pr_pagesize;
	long pr_filler[3];
  } prmap_t;

#define	MA_READ		0x04
#define	MA_WRITE	0x02
#define	MA_EXEC		0x01
#define	MA_SHARED	0x08
#define	MA_BREAK	0x10
#define	MA_STACK	0x20

typedef struct prcred
  {
	uid_t pr_euid;
	uid_t pr_ruid;
	uid_t pr_suid;
	gid_t pr_egid;
	gid_t pr_rgid;
	gid_t pr_sgid;
	unsigned int pr_ngroups;
  } prcred_t;

typedef struct prusage
  {
	id_t pr_lwpid;
	int pr_count;
	struct timespec pr_tstamp;
	struct timespec pr_create;
	struct timespec pr_term;
	struct timespec pr_rtime;
	struct timespec pr_utime;
	struct timespec pr_stime;
	struct timespec pr_ttime;
	struct timespec pr_tftime;
	struct timespec pr_dftime;
	struct timespec pr_kftime;
	struct timespec pr_ltime;
	struct timespec pr_slptime;
	struct timespec pr_wtime;
	struct timespec pr_stoptime;
	struct timespec	filltime[6];
	unsigned long pr_minf;
	unsigned long pr_majf;
	unsigned long pr_nswap;
	unsigned long pr_inblk;
	unsigned long pr_oublk;
	unsigned long pr_msnd;
	unsigned long pr_mrcv;
	unsigned long pr_sigs;
	unsigned long pr_vctx;
	unsigned long pr_ictx;
	unsigned long pr_sysc;
	unsigned long pr_ioch;
	unsigned long	filler[10];
  } prusage_t;

typedef struct prpageheader
  {
	struct timespec pr_tstamp;
	unsigned long pr_nmap;
	unsigned long pr_npage;
  } prpageheader_t;

typedef struct prasmap
  {
	caddr_t pr_vaddr;
	size_t pr_npage;
	off_t pr_off;
	unsigned int pr_mflags;
	unsigned int pr_pagesize;
	long pr_filler[3];
  } prasmap_t;

#define	PG_REFERENCED	0x02
#define	PG_MODIFIED	0x01
#define	PG_HWMAPPED	0x04

/* based on sig*set */

#define prfillset(set) \
	{ int __cnt = sizeof (*set) / sizeof (uint32_t); \
	while (--__cnt >= 0) ((uint32_t *)(set))[__cnt] = 0xFFFFFFFF; }

#define premptyset(set) \
	{ int __cnt = sizeof (*set) / sizeof (uint32_t); \
	while (--__cnt >= 0) ((uint32_t *)(set))[__cnt] = 0; }

#define __prmask(flag) \
  (((uint32_t) 1) << (((flag) - 1) % (8 * (int)sizeof (uint32_t))))

# define __prword(flag)	(((flag) - 1) / (8 * (int)sizeof (uint32_t)))

#define praddset(set, flag) \
    (((uint32_t *)(set))[__prword (flag)] |= __prmask (flag))

#define prdelset(set, flag) \
    (((uint32_t *)(set))[__prword (flag)] &= ~__prmask (flag))

#define prismember(set, flag) \
	((((uint32_t *)(set))[__prword (flag)] & __prmask (flag)) ? 1 : 0)

#endif /* _SYS_OLD_PROCFS_H */
