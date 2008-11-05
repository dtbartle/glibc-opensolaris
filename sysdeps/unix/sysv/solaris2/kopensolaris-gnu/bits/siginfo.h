/* siginfo_t, sigevent and constants.  OpenSolaris version.
   Copyright (C) 1997-2002, 2003, 2008 Free Software Foundation, Inc.
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

#if !defined _SIGNAL_H && !defined __need_siginfo_t \
    && !defined __need_sigevent_t
# error "Never include this file directly.  Use <signal.h> instead"
#endif

#include <bits/wordsize.h>
#include <features.h>

/* This needs to be defined here because we only get timespec for certain
   posix flags.  */
#if !defined __USE_POSIX199309 && !defined __USE_MISC
struct __timespec
  {
    __time_t tv_sec;        /* Seconds.  */
    long int tv_nsec;       /* Nanoseconds.  */
  };
#else
# define __need_timespec
# include <time.h>
#endif

#if (!defined __have_sigval_t \
     && (defined _SIGNAL_H || defined __need_siginfo_t \
	 || defined __need_sigevent_t))
# define __have_sigval_t	1

/* Type for data associated with a signal.  */
union sigval
{
    int sival_int;
    void *sival_ptr;
};
typedef union sigval sigval_t;

# ifdef _SYSCALL32

# include <sys/types32.h>

union sigval32
  {
	__int32_t sival_int;
	caddr32_t sival_ptr;
  };

# endif

#endif

#if (!defined __have_siginfo_t \
     && (defined _SIGNAL_H || defined __need_siginfo_t))
# define __have_siginfo_t	1

# if __WORDSIZE == 64
# define __SI_MAX_SIZE     256
# define __SI_PAD_SIZE     ((__SI_MAX_SIZE / sizeof (int)) - 4)
# else
# define __SI_MAX_SIZE     128
# define __SI_PAD_SIZE     ((__SI_MAX_SIZE / sizeof (int)) - 3)
# endif
# define SI_MAXSZ          __SI_MAX_SIZE
# define SI_PAD            __SI_PAD_SIZE

typedef struct siginfo
{
    int si_signo;
    int si_code;
    int si_errno;
# if __WORDSIZE == 64
    int si_pad;
# endif
    union
    {
        int _pad[__SI_PAD_SIZE];

        struct /* kill(), SIGCLD, siqqueue() */
        {
            __pid_t __pid;	/* Sending process ID.  */
            union {
                struct {
                    __uid_t __uid;	/* Real user ID of sending process.  */
                    union sigval  __value;
                } __kill;
                struct {
                    __clock_t __utime;
                    int __status;
                    __clock_t __stime;
                } __cld;
            } __pdata;
            ctid_t __ctid;
            zoneid_t __zoneid;
        } __proc;

        struct /* SIGSEGV, SIGBUS, SIGILL, SIGTRAP, SIGFPE */
        {
            void *__addr;
            int __trapno;
            char *__pc;
        } __fault;

        struct /* SIGPOLL, SIGXFSZ */
        {
            int __fd;
            long  __band;
        } __file;

        struct /* SIGPROF */
        {
            char *__faddr;
#if !defined __USE_POSIX199309 && !defined __USE_MISC
            struct __timespec __tstamp;
#else
            struct timespec __tstamp;
#endif
            short __syscall;
            char  __nsysarg;
            char  __fault;
            long  __sysarg[8];
            int __mstate[10];
        } __prof;

        struct /* SI_RCTL */
        {
            __int32_t __entity;
        } __rctl;
    } __data;
} siginfo_t;

# ifdef _SYSCALL32

#  include <sys/types32.h>

typedef struct siginfo32
{
    int32_t si_signo;
    int32_t si_code;
    int32_t si_errno;
    union
    {
        int32_t _pad[__SI_PAD_SIZE];

        struct /* kill(), SIGCLD, siqqueue() */
        {
            pid32_t __pid;	/* Sending process ID.  */
            union {
                struct {
                    uid32_t __uid;	/* Real user ID of sending process.  */
                    union sigval32  __value;
                } __kill;
                struct {
                    clock32_t __utime;
                    int32_t __status;
                    clock32_t __stime;
                } __cld;
            } __pdata;
            id32_t __ctid;
            id32_t __zoneid;
        } __proc;

        struct /* SIGSEGV, SIGBUS, SIGILL, SIGTRAP, SIGFPE */
        {
            caddr32_t __addr;
            int32_t __trapno;
            caddr32_t __pc;
        } __fault;

        struct /* SIGPOLL, SIGXFSZ */
        {
            int32_t __fd;
            int32_t  __band;
        } __file;

        struct /* SIGPROF */
        {
            caddr32_t __faddr;
            struct timespec32 __tstamp;
            int16_t __syscall;
            int8_t  __nsysarg;
            int8_t  __fault;
            int32_t  __sysarg[8];
            int32_t __mstate[10];
        } __prof;

        struct /* SI_RCTL */
        {
            int32_t __entity;
        } __rctl;
    } __data;
} siginfo32_t;

# endif /* _SYSCALL32 */

# ifdef __USE_MISC

typedef struct k_siginfo
{
	int si_signo;
	int si_code;
	int si_errno;
#  if __WORDSIZE == 64
	int si_pad;
#  endif
	union
	  {
		struct
		  {
			__pid_t __pid;
			union
			  {
				struct
				  {
					__uid_t __uid;
                    union sigval __value;
				  } __kill;
                struct
				  {
					__clock_t __utime;
					int __status;
					__clock_t __stime;
				  } __cld;
			  } __pdata;
			ctid_t __ctid;
			zoneid_t __zoneid;
		  } __proc;

		struct
		  {
			void *__addr;
			int __trapno;
            char *__pc;
		  } __fault;

		struct
		  {
			int __fd;
			long __band;
		  } __file;

		struct
		  {
			char *__faddr;

            struct timespec __tstamp;
            short __syscall;
            char __nsysarg;
            char __fault;
		  } __prof;

		struct
		  {
			int32_t __entity;
		  } __rctl;
	  } __data;
  } k_siginfo_t;

typedef struct sigqueue
  {
	struct sigqueue *sq_next;
	k_siginfo_t sq_info;
	void (*sq_func)(struct sigqueue *);
	void *sq_backptr;
	int sq_external;
  } sigqueue_t;

# endif /* __USE_MISC */

# define SI_FROMUSER(sip)  ((sip)->si_code <= 0)
# define SI_FROMKERNEL(sip)  ((sip)->si_code > 0)

/* Values for `si_code'.  Positive values are reserved for kernel-generated
   signals.  */
enum
{
    SI_NOINFO = 32767, /* no signal information */
# define SI_NOINFO SI_NOINFO
    SI_DTRACE = 2050, /* kernel generated signal via DTrace action */
# define SI_DTRACE SI_DTRACE
    SI_RCTL = 2049, /* kernel generated signal via rctl action */
# define SI_RCTL SI_RCTL
    SI_USER = 0, /* user generated signal via kill() */
# define SI_USER SI_USER
    SI_LWP = -1, /* user generated signal via lwp_kill() */
# define SI_LWP SI_LWP
    SI_QUEUE = -2, /* user generated signal via sigqueue() */
# define SI_QUEUE SI_QUEUE
    SI_TIMER = -3, /* from timer expiration */
# define SI_TIMER SI_TIMER
    SI_ASYNCIO = -4, /* from asynchronous I/O completion */
# define SI_ASYNCIO SI_ASYNCIO
    SI_MESGQ = -5 /* from message arrival */
};

/* `si_code' values for SIGILL signal.  */
enum
{
  ILL_ILLOPC = 1,		/* Illegal opcode.  */
# define ILL_ILLOPC	ILL_ILLOPC
  ILL_ILLOPN = 2,		/* Illegal operand.  */
# define ILL_ILLOPN	ILL_ILLOPN
  ILL_ILLADR = 3,		/* Illegal addressing mode.  */
# define ILL_ILLADR	ILL_ILLADR
  ILL_ILLTRP = 4,		/* Illegal trap. */
# define ILL_ILLTRP	ILL_ILLTRP
  ILL_PRVOPC = 5,		/* Privileged opcode.  */
# define ILL_PRVOPC	ILL_PRVOPC
  ILL_PRVREG = 6,		/* Privileged register.  */
# define ILL_PRVREG	ILL_PRVREG
  ILL_COPROC = 7,		/* Coprocessor error.  */
# define ILL_COPROC	ILL_COPROC
  ILL_BADSTK = 8		/* Internal stack error.  */
# define ILL_BADSTK	ILL_BADSTK
};
# define NSIGILL	8

/* `si_code' values for SIGFPE signal.  */
enum
{
  FPE_INTDIV = 1,		/* Integer divide by zero.  */
# define FPE_INTDIV	FPE_INTDIV
  FPE_INTOVF = 2,		/* Integer overflow.  */
# define FPE_INTOVF	FPE_INTOVF
  FPE_FLTDIV = 3,		/* Floating point divide by zero.  */
# define FPE_FLTDIV	FPE_FLTDIV
  FPE_FLTOVF = 4,		/* Floating point overflow.  */
# define FPE_FLTOVF	FPE_FLTOVF
  FPE_FLTUND = 5,		/* Floating point underflow.  */
# define FPE_FLTUND	FPE_FLTUND
  FPE_FLTRES = 6,		/* Floating point inexact result.  */
# define FPE_FLTRES	FPE_FLTRES
  FPE_FLTINV = 7,		/* Floating point invalid operation.  */
# define FPE_FLTINV	FPE_FLTINV
  FPE_FLTSUB = 8,		/* Subscript out of range.  */
# define FPE_FLTSUB	FPE_FLTSUB
  FPE_FLTDEN = 9
# define FPE_FLTDEN	FPE_FLTDEN
};
# define NSIGFPE	9

/* `si_code' values for SIGSEGV signal.  */
enum
{
  SEGV_MAPERR = 1,		/* Address not mapped to object.  */
# define SEGV_MAPERR	SEGV_MAPERR
  SEGV_ACCERR = 2		/* Invalid permissions for mapped object.  */
# define SEGV_ACCERR	SEGV_ACCERR
};
# define NSIGSEGV	2

/* `si_code' values for SIGBUS signal.  */
enum
{
  BUS_ADRALN = 1,		/* Invalid address alignment.  */
# define BUS_ADRALN	BUS_ADRALN
  BUS_ADRERR = 2,		/* Non-existant physical address.  */
# define BUS_ADRERR	BUS_ADRERR
  BUS_OBJERR = 3		/* Object specific hardware error.  */
# define BUS_OBJERR	BUS_OBJERR
};
# define NSIGBUS	3

/* `si_code' values for SIGEMT signal.  */
enum
{
  EMT_CPCOVF = 1
# define EMT_CPCOVF	EMT_CPCOVF
};
# define NSIGEMT	1


/* `si_code' values for SIGTRAP signal.  */
# define TRAP_BRKPT  1 /* breakpoint trap */
# define TRAP_TRACE  2 /* trace trap */
# define TRAP_RWATCH 3 /* read access watchpoint trap */
# define TRAP_WWATCH 4 /* write access watchpoint trap */
# define TRAP_XWATCH 5 /* execute access watchpoint trap */
# define TRAP_DTRACE 6 /* problem with fasttrap DTrace provider */
# define NSIGTRAP  6

/* `si_code' values for SIGCHLD signal.  */
# define CLD_EXITED  1 /* child has exited */
# define CLD_KILLED  2 /* child was killed */
# define CLD_DUMPED  3 /* child has coredumped */
# define CLD_TRAPPED 4 /* traced child has stopped */
# define CLD_STOPPED 5 /* child has stopped on signal */
# define CLD_CONTINUED 6 /* stopped child has continued */
# define NSIGCLD   6

/* `si_code' values for SIGPOLL signal.  */
# define POLL_IN   1 /* input available */
# define POLL_OUT  2 /* output possible */
# define POLL_MSG  3 /* message available */
# define POLL_ERR  4 /* I/O error */
# define POLL_PRI  5 /* high priority input available */
# define POLL_HUP  6 /* device disconnected */
# define NSIGPOLL  6

/* SIGPROF signal codes */
# define PROF_SIG  1 /* have to set code non-zero */
# define NSIGPROF  1

/* X/Open requires some more fields with fixed names.  */
# define si_pid    __data.__proc.__pid
# define si_ctid   __data.__proc.__ctid
# define si_zoneid __data.__proc.__zoneid
# define si_status __data.__proc.__pdata.__cld.__status
# define si_stime  __data.__proc.__pdata.__cld.__stime
# define si_utime  __data.__proc.__pdata.__cld.__utime
# define si_uid    __data.__proc.__pdata.__kill.__uid
# define si_value  __data.__proc.__pdata.__kill.__value
# define si_addr   __data.__fault.__addr
# define si_trapno __data.__fault.__trapno
# define si_trapafter  __data.__fault.__trapno
# define si_pc   __data.__fault.__pc
# define si_fd   __data.__file.__fd
# define si_band   __data.__file.__band
# define si_tstamp __data.__prof.__tstamp
# define si_syscall  __data.__prof.__syscall
# define si_nsysarg  __data.__prof.__nsysarg
# define si_sysarg __data.__prof.__sysarg
# define si_fault  __data.__prof.__fault
# define si_faddr  __data.__prof.__faddr
# define si_mstate __data.__prof.__mstate
# define si_entity __data.__rctl.__entity

# undef __need_siginfo_t
#endif	/* !have siginfo_t && (have _SIGNAL_H || need siginfo_t).  */

#if (defined _SIGNAL_H || defined __need_sigevent_t) \
    && !defined __have_sigevent_t
# define __have_sigevent_t	1

/* Structure to transport application-defined values with signals.  */
# define __SIGEV_MAX_SIZE	64
# if __WORDSIZE == 64
#  define __SIGEV_PAD_SIZE	((__SIGEV_MAX_SIZE / sizeof (int)) - 4)
# else
#  define __SIGEV_PAD_SIZE	((__SIGEV_MAX_SIZE / sizeof (int)) - 3)
# endif

typedef struct sigevent
{
    int sigev_notify;
    int sigev_signo;
    union sigval sigev_value;
    void (*sigev_notify_function)(union sigval);
    /*pthread_attr_t*/ void *sigev_notify_attributes;
    int  __sigev_pad2;
} sigevent_t;

#ifdef _SYSCALL32

#include <sys/types32.h>

struct sigevent32
  {
	__int32_t sigev_notify;
	__int32_t sigev_signo;
	union sigval32 sigev_value;
	caddr32_t sigev_notify_function;
	caddr32_t sigev_notify_attributes;
	__int32_t __sigev_pad2;
};

#endif

/* `sigev_notify' values.  */
enum
{
  SIGEV_NONE = 1, /* no notification */
# define SIGEV_NONE	SIGEV_NONE
  SIGEV_SIGNAL = 2, /* queued signal notification */
# define SIGEV_SIGNAL	SIGEV_SIGNAL
  SIGEV_THREAD = 3, /* call back from another thread */
#define SIGEV_PORT SIGEV_PORT
  SIGEV_PORT = 4 /* use event port for notification */
#define SIGEV_PORT SIGEV_PORT
};

#endif	/* have _SIGNAL_H.  */
