/* Declarations of procfs structures.
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

#ifndef _SYS_PROCFS_H
#define _SYS_PROCFS_H	1

#include <sys/types.h>
#include <sys/signal.h>
#include <sys/fault.h>
#include <sys/syscall.h>
#include <sys/processor.h>
#include <sys/pset.h>
#include <sys/priv.h>
#include <bits/regset.h>
#include <time.h>
#include <bits/wordsize.h>
#include <sys/isa_defs.h>

/* control codes for ctl and lwpctl */
#define PCNULL		0
#define PCSTOP		1
#define PCDSTOP		2
#define PCWSTOP		3
#define PCTWSTOP	4
#define PCRUN		5
#define PCCSIG		6
#define PCCFAULT	7
#define PCSSIG		8
#define PCKILL		9
#define PCUNKILL	10
#define PCSHOLD		11
#define PCSTRACE	12
#define PCSFAULT	13
#define PCSENTRY	14
#define PCSEXIT		15
#define PCSET		16
#define PCUNSET		17
#define PCSREG		18
#define PCSFPREG	19
#define PCSXREG		20
#define PCNICE		21
#define PCSVADDR	22
#define PCWATCH		23
#define PCAGENT		24
#define PCREAD		25
#define PCWRITE		26
#define PCSCRED		27
#define PCSASRS		28
#define PCSPRIV		29
#define PCSZONE		30
#define PCSCREDX	31

/* PCRUN codes */
#define PRCSIG		0x01
#define PRCFAULT	0x02
#define PRSTEP		0x04
#define PRSABORT	0x08
#define PRSTOP		0x10

/* /proc/<pid>/lwp/<lwpid>/lwpstatus */
typedef struct lwpstatus
{
	int	pr_flags;
	id_t pr_lwpid;
	short pr_why;
	short pr_what;
	short pr_cursig;
	short pr_pad1;
	siginfo_t pr_info;
	sigset_t pr_lwppend;
	sigset_t pr_lwphold;
	struct sigaction pr_action;
	stack_t	pr_altstack;
	uintptr_t pr_oldcontext;
	short pr_syscall;
	short pr_nsysarg;
	int	pr_errno;
#define	PRSYSARGS	8
	long pr_sysarg[PRSYSARGS];
	long pr_rval1;
	long pr_rval2;
#define	PRCLSZ		8
	char pr_clname[PRCLSZ];
	struct timespec pr_tstamp;
	struct timespec pr_utime;
	struct timespec pr_stime;
	int	pr_filler[11 - 2 * sizeof (struct timespec) / sizeof (int)];
	int	pr_errpriv;
	uintptr_t pr_ustack;
	unsigned long pr_instr;
	prgregset_t pr_reg;
	prfpregset_t pr_fpreg;
} lwpstatus_t;

/* /proc/<pid>/status */
typedef struct pstatus
{
	int	pr_flags;
	int	pr_nlwp;
	pid_t pr_pid;
	pid_t pr_ppid;
	pid_t pr_pgid;
	pid_t pr_sid;
	id_t pr_aslwpid;
	id_t pr_agentid;
	sigset_t pr_sigpend;
	uintptr_t pr_brkbase;
	size_t pr_brksize;
	uintptr_t pr_stkbase;
	size_t pr_stksize;
	struct timespec pr_utime;
	struct timespec pr_stime;
	struct timespec pr_cutime;
	struct timespec pr_cstime;
	sigset_t pr_sigtrace;
	fltset_t pr_flttrace;
	sysset_t pr_sysentry;
	sysset_t pr_sysexit;
	char pr_dmodel;
	char pr_pad[3];
	taskid_t pr_taskid;
	projid_t pr_projid;
	int pr_nzomb;
	zoneid_t pr_zoneid;
	int pr_filler[15];
	lwpstatus_t pr_lwp;
} pstatus_t;

/* pr_flags */
#define	PR_STOPPED		0x00000001
#define	PR_ISTOP		0x00000002
#define	PR_DSTOP		0x00000004
#define	PR_STEP			0x00000008
#define	PR_ASLEEP		0x00000010
#define	PR_PCINVAL		0x00000020
#define	PR_ASLWP		0x00000040
#define	PR_AGENT		0x00000080
#define	PR_DETACH		0x00000100
#define	PR_DAEMON		0x00000200
#define	PR_IDLE			0x00000400
#define	PR_ISSYS		0x00001000
#define	PR_VFORKP		0x00002000
#define	PR_ORPHAN		0x00004000
#define	PR_NOSIGCHLD	0x00008000
#define	PR_WAITPID	    0x00010000
#define	PR_FORK			0x00100000
#define	PR_RLC			0x00200000
#define	PR_KLC			0x00400000
#define	PR_ASYNC		0x00800000
#define	PR_MSACCT		0x01000000
#define	PR_BPTADJ		0x02000000
#define	PR_PTRACE		0x04000000
#define	PR_MSFORK		0x08000000

/* pr_why */
enum
{
	PR_REQUESTED = 1,
#define	PR_REQUESTED PR_REQUESTED
	PR_SIGNALLED = 2,
#define	PR_SIGNALLED PR_SIGNALLED
	PR_SYSENTRY = 3,
#define	PR_SYSENTRY PR_SYSENTRY
	PR_SYSEXIT = 4,
#define	PR_SYSEXIT PR_SYSEXIT
	PR_JOBCONTROL = 5,
#define	PR_JOBCONTROL PR_JOBCONTROL
	PR_FAULTED = 6,
#define	PR_FAULTED PR_FAULTED
	PR_SUSPENDED = 7,
#define	PR_SUSPENDED PR_SUSPENDED
	PR_CHECKPOINT = 8
#define	PR_CHECKPOINT PR_CHECKPOINT
};

/* /proc/<pid>/lwp/<lwpid>/lwpsinfo */
typedef struct lwpsinfo
{
	int	pr_flag;
	id_t	pr_lwpid;
	uintptr_t pr_addr;
	uintptr_t pr_wchan;
	char pr_stype;
	char pr_state;
	char pr_sname;
	char pr_nice;
	short pr_syscall;
	char pr_oldpri;
	char pr_cpu;
	int	pr_pri;
	unsigned short pr_pctcpu;
	unsigned short pr_pad;
	struct timespec pr_start;
	struct timespec pr_time;
#define	PRFNSZ		16
	char pr_clname[PRCLSZ];
	char pr_name[PRFNSZ];
	processorid_t pr_onpro;
	processorid_t pr_bindpro;
	psetid_t pr_bindpset;
	int	pr_lgrp;
	int	pr_filler[4];
} lwpsinfo_t;

/* pr_ttydev: non-existent device */
#define	PRNODEV	(dev_t)(-1)

/* /proc/<pid>/psinfo */
typedef struct psinfo
{
	int	pr_flag;
	int	pr_nlwp;
	pid_t pr_pid;
	pid_t pr_ppid;
	pid_t pr_pgid;
	pid_t pr_sid;
	uid_t pr_uid;
	uid_t pr_euid;
	gid_t pr_gid;
	gid_t pr_egid;
	uintptr_t pr_addr;
	size_t pr_size;
	size_t pr_rssize;
	size_t pr_pad1;
	dev_t pr_ttydev;
	unsigned short pr_pctcpu;
	unsigned short pr_pctmem;
	struct timespec pr_start;
	struct timespec pr_time;
	struct timespec pr_ctime;
	char pr_fname[PRFNSZ];
#define	PRARGSZ		80
	char pr_psargs[PRARGSZ];
	int pr_wstat;
	int pr_argc;
	uintptr_t pr_argv;
	uintptr_t pr_envp;
	char pr_dmodel;
	char pr_pad2[3];
	taskid_t pr_taskid;
	projid_t pr_projid;
	int pr_nzomb;
	poolid_t pr_poolid;
	zoneid_t pr_zoneid;
	id_t pr_contract;
	int pr_filler[1];
	lwpsinfo_t pr_lwp;
} psinfo_t;

/* /proc/<pid>/map, /proc/<pid>/rmap */
typedef struct prmap
{
	uintptr_t pr_vaddr;
	size_t pr_size;
#define	PRMAPSZ	64
	char pr_mapname[PRMAPSZ];
	offset_t pr_offset;
	int pr_mflags;
	int pr_pagesize;
	int pr_shmid;
	int pr_filler[1];
} prmap_t;

/* pr_mflags values */
#define	MA_EXEC			0x0001
#define	MA_WRITE		0x0002
#define	MA_READ			0x0004
#define	MA_SHARED		0x0008
#define	MA_BREAK		0x0010
#define	MA_STACK		0x0020
#define	MA_ANON			0x0040
#define	MA_ISM			0x0080
#define	MA_NORESERVE	0x0100
#define	MA_SHM			0x0200
#define	MA_RESERVED1	0x0400

/* /proc/<pid>/xmap */
typedef struct prxmap
{
	uintptr_t pr_vaddr;
	size_t pr_size;
	char pr_mapname[PRMAPSZ];
	offset_t pr_offset;
	int pr_mflags;
	int pr_pagesize;
	int pr_shmid;
	dev_t pr_dev;
	uint64_t pr_ino;
	size_t pr_rss;
	size_t pr_anon;
	size_t pr_locked;
	size_t pr_pad;
	uint64_t pr_hatpagesize;
#if __WORDSIZE == 32
	unsigned long pr_filler[6];
#else
	unsigned long pr_filler[7];
#endif
} prxmap_t;

/* pr_mflags */
#define MA_EXEC			0x0001
#define MA_WRITE		0x0002
#define MA_READ			0x0004
#define MA_SHARED		0x0008
#define MA_ANON			0x0040
#define MA_ISM			0x0080
#define MA_NORESERVE	0x0100
#define MA_SHM			0x0200
#define MA_RESERVED1	0x0400

/* /proc/<pid>/cred */
typedef struct prcred
{
	uid_t pr_euid;
	uid_t pr_ruid;
	uid_t pr_suid;
	gid_t pr_egid;
	gid_t pr_rgid;
	gid_t pr_sgid;
	int pr_ngroups;
	gid_t pr_groups[1];
} prcred_t;

/* /proc/<pid>/priv */
typedef struct prpriv
{
	uint32_t pr_nsets;
	uint32_t pr_setsize;
	uint32_t pr_infosize;
	priv_chunk_t pr_sets[1];
} prpriv_t;

/* /proc/<pid>/watch */
typedef struct prwatch
{
	uintptr_t pr_vaddr;
	size_t pr_size;
	int pr_wflags;
	int pr_pad;
} prwatch_t;

/* pr_wflags */
#define WA_EXEC			0x01
#define WA_WRITE		0x02
#define WA_READ			0x04
#define WA_TRAPAFTER	0x08

typedef struct priovec {
	void *pio_base;
	size_t pio_len;
	off_t pio_offset;
} priovec_t;

/* /proc/<pid>/usage, /proc/<pid>/lwp/<lwpid>/lwpusage */
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
	struct timespec filltime[6];
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
	unsigned long filler[10];
} prusage_t;

/* /proc/<pid>/pagedata file header */
typedef struct prpageheader
{
	struct timespec pr_tstamp;
	long pr_nmap;
	long pr_npage;
} prpageheader_t;

/* /proc/<pid>/pagedata mapping header */
typedef struct prasmap
{
	uintptr_t pr_vaddr;
	size_t pr_npage;
	char pr_mapname[PRMAPSZ];
	offset_t pr_offset;
	int pr_mflags;
	int pr_pagesize;
	int pr_shmid;
	int pr_filler[1];
} prasmap_t;

/* pr_npage-long byte array (plus 8-byte alignment) of the following flags */
#define	PG_REFERENCED	0x02
#define	PG_MODIFIED		0x01
#define	PG_HWMAPPED		0x04

/* /proc/<pid>/lstatus, /proc/<pid>/lpsinfo, /proc/<pid>/lusage header */
typedef struct prheader
{
	long pr_nent;
	long pr_entsize;
} prheader_t;

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

/* Data models.  */
#define PR_MODEL_UNKNOWN	0
#define PR_MODEL_ILP32	1
#define PR_MODEL_LP64   2
#if defined(_LP64)
# define PR_MODEL_NATIVE	PR_MODEL_LP64
#elif defined(_ILP32)
# define PR_MODEL_NATIVE	PR_MODEL_ILP32
#else
# error Unknown data model
#endif

typedef uchar_t instr_t;

#endif /* _SYS_PROCFS_H */
