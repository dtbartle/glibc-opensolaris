/* `sysconf', `pathconf', and `confstr' NAME values.  OpenSolaris version.
   Copyright (C) 1993,1995-1998,2000,2001,2003,2004,2007,2008
   Free Software Foundation, Inc.
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

#ifndef _UNISTD_H
# error "Never use <bits/confname.h> directly; include <unistd.h> instead."
#endif

/* Values for the NAME argument to `pathconf' and `fpathconf'.  */
enum
  {
    _PC_LINK_MAX = 1,
#define	_PC_LINK_MAX			_PC_LINK_MAX
    _PC_MAX_CANON = 2,
#define	_PC_MAX_CANON			_PC_MAX_CANON
    _PC_MAX_INPUT = 3,
#define	_PC_MAX_INPUT			_PC_MAX_INPUT
    _PC_NAME_MAX = 4,
#define	_PC_NAME_MAX			_PC_NAME_MAX
    _PC_PATH_MAX = 5,
#define	_PC_PATH_MAX			_PC_PATH_MAX
    _PC_PIPE_BUF = 6,
#define	_PC_PIPE_BUF			_PC_PIPE_BUF
    _PC_NO_TRUNC = 7,
#define	_PC_NO_TRUNC			_PC_NO_TRUNC
    _PC_VDISABLE = 8,
#define _PC_VDISABLE			_PC_VDISABLE
    _PC_CHOWN_RESTRICTED = 9,
#define	_PC_CHOWN_RESTRICTED		_PC_CHOWN_RESTRICTED
    _PC_ASYNC_IO = 10,
#define	_PC_ASYNC_IO			_PC_ASYNC_IO
    _PC_PRIO_IO = 11,
#define	_PC_PRIO_IO			_PC_PRIO_IO
    _PC_SYNC_IO = 12,
#define	_PC_SYNC_IO			_PC_SYNC_IO
    _PC_ALLOC_SIZE_MIN = 13,
#define _PC_ALLOC_SIZE_MIN		_PC_ALLOC_SIZE_MIN
    _PC_REC_INCR_XFER_SIZE = 14,
#define _PC_REC_INCR_XFER_SIZE		_PC_REC_INCR_XFER_SIZE
    _PC_REC_MAX_XFER_SIZE = 15,
#define _PC_REC_MAX_XFER_SIZE		_PC_REC_MAX_XFER_SIZE
    _PC_REC_MIN_XFER_SIZE = 16,
#define _PC_REC_MIN_XFER_SIZE		_PC_REC_MIN_XFER_SIZE
    _PC_REC_XFER_ALIGN = 17,
#define _PC_REC_XFER_ALIGN		_PC_REC_XFER_ALIGN
    _PC_SYMLINK_MAX = 18,
#define _PC_SYMLINK_MAX			_PC_SYMLINK_MAX
    _PC_2_SYMLINKS = 19,
#define _PC_2_SYMLINKS			_PC_2_SYMLINKS
/* _PC_ACL_ENABLED to _PC_SATTR_EXISTS */ /* OpenSolaris */

    _PC_FILESIZEBITS = 67,
#define _PC_FILESIZEBITS		_PC_FILESIZEBITS

    _PC_XATTR_ENABLED = 100,
#define PC_XATTR_ENABLED		PC_XATTR_ENABLED
    _PC_XATTR_EXISTS = 101,
#define _PC_XATTR_EXISTS		_PC_XATTR_EXISTS

/* These are found in GNU libc but not OpenSolaris. */

    _PC_SOCK_MAXBUF = 5501,
#define	_PC_SOCK_MAXBUF			_PC_SOCK_MAXBUF
  };

/* Values for the argument to `sysconf'.  */
enum
  {
    _SC_ARG_MAX = 1,
#define	_SC_ARG_MAX			_SC_ARG_MAX
    _SC_CHILD_MAX = 2,
#define	_SC_CHILD_MAX			_SC_CHILD_MAX
    _SC_CLK_TCK = 3,
#define	_SC_CLK_TCK			_SC_CLK_TCK
    _SC_NGROUPS_MAX = 4,
#define	_SC_NGROUPS_MAX			_SC_NGROUPS_MAX
    _SC_OPEN_MAX = 5,
#define	_SC_OPEN_MAX			_SC_OPEN_MAX
    _SC_JOB_CONTROL = 6,
#define	_SC_JOB_CONTROL			_SC_JOB_CONTROL
    _SC_SAVED_IDS = 7,
#define	_SC_SAVED_IDS			_SC_SAVED_IDS
    _SC_VERSION = 8,
#define	_SC_VERSION			_SC_VERSION
    _SC_PASS_MAX = 9,
#define _SC_PASS_MAX			_SC_PASS_MAX
	_SC_LOGNAME_MAX = 10,
#define _SC_LOGNAME_MAX			_SC_LOGNAME_MAX
    _SC_PAGESIZE = 11,
#define	_SC_PAGESIZE			_SC_PAGESIZE
#define	_SC_PAGE_SIZE			_SC_PAGESIZE
    _SC_XOPEN_VERSION = 12,
#define _SC_XOPEN_VERSION		_SC_XOPEN_VERSION
/* _SC_NACLS_MAX = 13 */
    _SC_NPROCESSORS_CONF = 14,
#define _SC_NPROCESSORS_CONF		_SC_NPROCESSORS_CONF
    _SC_NPROCESSORS_ONLN = 15,
#define _SC_NPROCESSORS_ONLN		_SC_NPROCESSORS_ONLN
    _SC_STREAM_MAX = 16,
#define	_SC_STREAM_MAX			_SC_STREAM_MAX
    _SC_TZNAME_MAX = 17,
#define	_SC_TZNAME_MAX			_SC_TZNAME_MAX
    _SC_AIO_LISTIO_MAX = 18,
#define	_SC_AIO_LISTIO_MAX		_SC_AIO_LISTIO_MAX
    _SC_AIO_MAX = 19,
#define	_SC_AIO_MAX			_SC_AIO_MAX
    _SC_AIO_PRIO_DELTA_MAX = 20,
#define	_SC_AIO_PRIO_DELTA_MAX		_SC_AIO_PRIO_DELTA_MAX
    _SC_ASYNCHRONOUS_IO = 21,
#define	_SC_ASYNCHRONOUS_IO		_SC_ASYNCHRONOUS_IO
    _SC_DELAYTIMER_MAX = 22,
#define	_SC_DELAYTIMER_MAX		_SC_DELAYTIMER_MAX
    _SC_FSYNC = 23,
#define	_SC_FSYNC			_SC_FSYNC
    _SC_MAPPED_FILES = 24,
#define	_SC_MAPPED_FILES		_SC_MAPPED_FILES
    _SC_MEMLOCK = 25,
#define	_SC_MEMLOCK			_SC_MEMLOCK
    _SC_MEMLOCK_RANGE = 26,
#define	_SC_MEMLOCK_RANGE		_SC_MEMLOCK_RANGE
    _SC_MEMORY_PROTECTION = 27,
#define	_SC_MEMORY_PROTECTION		_SC_MEMORY_PROTECTION
    _SC_MESSAGE_PASSING = 28,
#define	_SC_MESSAGE_PASSING		_SC_MESSAGE_PASSING
    _SC_MQ_OPEN_MAX = 29,
#define	_SC_MQ_OPEN_MAX			_SC_MQ_OPEN_MAX
    _SC_MQ_PRIO_MAX = 30,
#define	_SC_MQ_PRIO_MAX			_SC_MQ_PRIO_MAX
    _SC_PRIORITIZED_IO = 31,
#define	_SC_PRIORITIZED_IO		_SC_PRIORITIZED_IO
    _SC_PRIORITY_SCHEDULING = 32,
#define	_SC_PRIORITY_SCHEDULING		_SC_PRIORITY_SCHEDULING
    _SC_REALTIME_SIGNALS = 33,
#define	_SC_REALTIME_SIGNALS		_SC_REALTIME_SIGNALS
    _SC_RTSIG_MAX = 34,
#define	_SC_RTSIG_MAX			_SC_RTSIG_MAX
    _SC_SEMAPHORES = 35,
#define	_SC_SEMAPHORES			_SC_SEMAPHORES
    _SC_SEM_NSEMS_MAX = 36,
#define	_SC_SEM_NSEMS_MAX		_SC_SEM_NSEMS_MAX
    _SC_SEM_VALUE_MAX = 37,
#define	_SC_SEM_VALUE_MAX		_SC_SEM_VALUE_MAX
    _SC_SHARED_MEMORY_OBJECTS = 38,
#define	_SC_SHARED_MEMORY_OBJECTS	_SC_SHARED_MEMORY_OBJECTS
    _SC_SIGQUEUE_MAX = 39,
#define	_SC_SIGQUEUE_MAX		_SC_SIGQUEUE_MAX
    _SC_SIGRT_MIN = 40,
#define _SC_SIGRT_MIN			_SC_SIGRT_MIN
    _SC_SIGRT_MAX = 41,
#define _SC_SIGRT_MAX			_SC_SIGRT_MAX
    _SC_SYNCHRONIZED_IO = 42,
#define	_SC_SYNCHRONIZED_IO		_SC_SYNCHRONIZED_IO
    _SC_TIMERS = 43,
#define	_SC_TIMERS			_SC_TIMERS
    _SC_TIMER_MAX = 44,
#define	_SC_TIMER_MAX			_SC_TIMER_MAX
    _SC_2_C_BIND = 45,
#define	_SC_2_C_BIND			_SC_2_C_BIND
    _SC_2_C_DEV = 46,
#define	_SC_2_C_DEV			_SC_2_C_DEV
    _SC_2_C_VERSION = 47,
#define _SC_2_C_VERSION			_SC_2_C_VERSION
    _SC_2_FORT_DEV = 48,
#define	_SC_2_FORT_DEV			_SC_2_FORT_DEV
    _SC_2_FORT_RUN = 49,
#define	_SC_2_FORT_RUN			_SC_2_FORT_RUN
    _SC_2_LOCALEDEF = 50,
#define	_SC_2_LOCALEDEF			_SC_2_LOCALEDEF
    _SC_2_SW_DEV = 51,
#define	_SC_2_SW_DEV			_SC_2_SW_DEV
    _SC_2_UPE = 52,
#define _SC_2_UPE			_SC_2_UPE
    _SC_2_VERSION = 53,
#define	_SC_2_VERSION			_SC_2_VERSION
    _SC_BC_BASE_MAX = 54,
#define	_SC_BC_BASE_MAX			_SC_BC_BASE_MAX
    _SC_BC_DIM_MAX = 55,
#define	_SC_BC_DIM_MAX			_SC_BC_DIM_MAX
    _SC_BC_SCALE_MAX = 56,
#define	_SC_BC_SCALE_MAX		_SC_BC_SCALE_MAX
    _SC_BC_STRING_MAX = 57,
#define	_SC_BC_STRING_MAX		_SC_BC_STRING_MAX
    _SC_COLL_WEIGHTS_MAX = 58,
#define	_SC_COLL_WEIGHTS_MAX		_SC_COLL_WEIGHTS_MAX
    _SC_EXPR_NEST_MAX = 59,
#define	_SC_EXPR_NEST_MAX		_SC_EXPR_NEST_MAX
    _SC_LINE_MAX = 60,
#define	_SC_LINE_MAX			_SC_LINE_MAX
    _SC_RE_DUP_MAX = 61,
#define	_SC_RE_DUP_MAX			_SC_RE_DUP_MAX
    _SC_XOPEN_CRYPT = 62,
#define _SC_XOPEN_CRYPT			_SC_XOPEN_CRYPT
    _SC_XOPEN_ENH_I18N = 63,
#define _SC_XOPEN_ENH_I18N		_SC_XOPEN_ENH_I18N
    _SC_XOPEN_SHM = 64,
#define _SC_XOPEN_SHM			_SC_XOPEN_SHM

    _SC_2_CHAR_TERM = 66,
#define _SC_2_CHAR_TERM			_SC_2_CHAR_TERM
    _SC_XOPEN_XCU_VERSION = 67,
#define _SC_XOPEN_XCU_VERSION		_SC_XOPEN_XCU_VERSION

    _SC_ATEXIT_MAX,
#define _SC_ATEXIT_MAX			_SC_ATEXIT_MAX
    _SC_IOV_MAX = 77,
#define _SC_IOV_MAX			_SC_IOV_MAX
    _SC_UIO_MAXIOV = _SC_IOV_MAX,
#define	_SC_UIO_MAXIOV			_SC_UIO_MAXIOV
    _SC_XOPEN_UNIX = 78,
#define _SC_XOPEN_UNIX			_SC_XOPEN_UNIX
    _SC_T_IOV_MAX = 79,
#define	_SC_T_IOV_MAX			_SC_T_IOV_MAX

    _SC_PHYS_PAGES = 500,
#define _SC_PHYS_PAGES			_SC_PHYS_PAGES
    _SC_AVPHYS_PAGES = 501,
#define _SC_AVPHYS_PAGES		_SC_AVPHYS_PAGES

/* _SC_COHER_BLKSZ to _SC_EPHID_MAX */ /* OpenSolaris */

    _SC_THREAD_DESTRUCTOR_ITERATIONS = 568,
#define	_SC_THREAD_DESTRUCTOR_ITERATIONS _SC_THREAD_DESTRUCTOR_ITERATIONS
    _SC_GETGR_R_SIZE_MAX = 569,
#define	_SC_GETGR_R_SIZE_MAX		_SC_GETGR_R_SIZE_MAX
    _SC_GETPW_R_SIZE_MAX = 570,
#define	_SC_GETPW_R_SIZE_MAX		_SC_GETPW_R_SIZE_MAX
    _SC_LOGIN_NAME_MAX = 571,
#define	_SC_LOGIN_NAME_MAX		_SC_LOGIN_NAME_MAX
    _SC_THREAD_KEYS_MAX = 572,
#define	_SC_THREAD_KEYS_MAX		_SC_THREAD_KEYS_MAX
    _SC_THREAD_STACK_MIN = 573,
#define	_SC_THREAD_STACK_MIN		_SC_THREAD_STACK_MIN
    _SC_THREAD_THREADS_MAX = 574,
#define	_SC_THREAD_THREADS_MAX		_SC_THREAD_THREADS_MAX
    _SC_TTY_NAME_MAX = 575,
#define	_SC_TTY_NAME_MAX		_SC_TTY_NAME_MAX
    _SC_THREADS = 576,
#define	_SC_THREADS			_SC_THREADS
    _SC_THREAD_ATTR_STACKADDR = 577,
#define	_SC_THREAD_ATTR_STACKADDR	_SC_THREAD_ATTR_STACKADDR
    _SC_THREAD_ATTR_STACKSIZE = 578,
#define	_SC_THREAD_ATTR_STACKSIZE	_SC_THREAD_ATTR_STACKSIZE
    _SC_THREAD_PRIORITY_SCHEDULING = 579,
#define	_SC_THREAD_PRIORITY_SCHEDULING	_SC_THREAD_PRIORITY_SCHEDULING
    _SC_THREAD_PRIO_INHERIT = 580,
#define	_SC_THREAD_PRIO_INHERIT		_SC_THREAD_PRIO_INHERIT
    _SC_THREAD_PRIO_PROTECT = 581,
#define	_SC_THREAD_PRIO_PROTECT		_SC_THREAD_PRIO_PROTECT
    _SC_THREAD_PROCESS_SHARED = 582,
#define	_SC_THREAD_PROCESS_SHARED	_SC_THREAD_PROCESS_SHARED
    _SC_THREAD_SAFE_FUNCTIONS = 583,
#define _SC_THREAD_SAFE_FUNCTIONS	_SC_THREAD_SAFE_FUNCTIONS

    _SC_XOPEN_LEGACY = 717,
#define _SC_XOPEN_LEGACY		_SC_XOPEN_LEGACY
    _SC_XOPEN_REALTIME = 718,
#define _SC_XOPEN_REALTIME		_SC_XOPEN_REALTIME
    _SC_XOPEN_REALTIME_THREADS = 719,
#define _SC_XOPEN_REALTIME_THREADS	_SC_XOPEN_REALTIME_THREADS
    _SC_XBS5_ILP32_OFF32 = 720,
#define _SC_XBS5_ILP32_OFF32		_SC_XBS5_ILP32_OFF32
    _SC_XBS5_ILP32_OFFBIG = 721,
#define _SC_XBS5_ILP32_OFFBIG		_SC_XBS5_ILP32_OFFBIG
    _SC_XBS5_LP64_OFF64 = 722,
#define _SC_XBS5_LP64_OFF64		_SC_XBS5_LP64_OFF64
    _SC_XBS5_LPBIG_OFFBIG = 723,
#define _SC_XBS5_LPBIG_OFFBIG		_SC_XBS5_LPBIG_OFFBIG
    _SC_2_PBS = 724,
#define _SC_2_PBS			_SC_2_PBS
    _SC_2_PBS_ACCOUNTING = 725,
#define _SC_2_PBS_ACCOUNTING		_SC_2_PBS_ACCOUNTING
    _SC_2_PBS_CHECKPOINT = 726,
#define _SC_2_PBS_CHECKPOINT		_SC_2_PBS_CHECKPOINT
/* 727 */
    _SC_2_PBS_LOCATE = 728,
#define _SC_2_PBS_LOCATE		_SC_2_PBS_LOCATE
    _SC_2_PBS_MESSAGE = 729,
#define _SC_2_PBS_MESSAGE		_SC_2_PBS_MESSAGE
    _SC_2_PBS_TRACK = 730,
#define _SC_2_PBS_TRACK			_SC_2_PBS_TRACK
    _SC_ADVISORY_INFO = 731,
#define _SC_ADVISORY_INFO		_SC_ADVISORY_INFO
    _SC_BARRIERS = 732,
#define _SC_BARRIERS			_SC_BARRIERS
    _SC_CLOCK_SELECTION = 733,
#define _SC_CLOCK_SELECTION		_SC_CLOCK_SELECTION
    _SC_CPUTIME = 734,
#define _SC_CPUTIME			_SC_CPUTIME
    _SC_HOST_NAME_MAX = 735,
#define _SC_HOST_NAME_MAX		_SC_HOST_NAME_MAX
    _SC_MONOTONIC_CLOCK = 736,
#define _SC_MONOTONIC_CLOCK		_SC_MONOTONIC_CLOCK
    _SC_READER_WRITER_LOCKS = 737,
#define _SC_READER_WRITER_LOCKS		_SC_READER_WRITER_LOCKS
    _SC_REGEXP = 738,
#define _SC_REGEXP			_SC_REGEXP
    _SC_SHELL = 739,
#define _SC_SHELL			_SC_SHELL
    _SC_SPAWN = 740,
#define _SC_SPAWN			_SC_SPAWN
    _SC_SPIN_LOCKS = 741,
#define _SC_SPIN_LOCKS			_SC_SPIN_LOCKS
    _SC_SPORADIC_SERVER = 742,
#define _SC_SPORADIC_SERVER		_SC_SPORADIC_SERVER
    _SC_SS_REPL_MAX = 743,
#define _SC_SS_REPL_MAX			_SC_SS_REPL_MAX /* OpenSolaris */
    _SC_SYMLOOP_MAX = 744,
#define _SC_SYMLOOP_MAX			_SC_SYMLOOP_MAX
    _SC_THREAD_CPUTIME = 745,
#define _SC_THREAD_CPUTIME		_SC_THREAD_CPUTIME
    _SC_THREAD_SPORADIC_SERVER = 746,
#define _SC_THREAD_SPORADIC_SERVER	_SC_THREAD_SPORADIC_SERVER
    _SC_TIMEOUTS = 747,
#define _SC_TIMEOUTS			_SC_TIMEOUTS
    _SC_TRACE = 748,
#define _SC_TRACE			_SC_TRACE
    _SC_TRACE_EVENT_FILTER = 749,
#define _SC_TRACE_EVENT_FILTER		_SC_TRACE_EVENT_FILTER
    _SC_TRACE_EVENT_NAME_MAX = 750,
#define _SC_TRACE_EVENT_NAME_MAX	_SC_TRACE_EVENT_NAME_MAX /* OpenSolaris */
    _SC_TRACE_INHERIT = 751,
#define _SC_TRACE_INHERIT		_SC_TRACE_INHERIT
    _SC_TRACE_LOG = 752,
#define _SC_TRACE_LOG			_SC_TRACE_LOG
    _SC_TRACE_NAME_MAX = 753,
#define _SC_TRACE_NAME_MAX		_SC_TRACE_NAME_MAX /* OpenSolaris */
    _SC_TRACE_SYS_MAX = 754,
#define _SC_TRACE_SYS_MAX		_SC_TRACE_SYS_MAX /* OpenSolaris */
    _SC_TRACE_USER_EVENT_MAX = 755,
#define _SC_TRACE_USER_EVENT_MAX	_SC_TRACE_USER_EVENT_MAX /* OpenSolaris */
    _SC_TYPED_MEMORY_OBJECTS = 756,
#define _SC_TYPED_MEMORY_OBJECTS	_SC_TYPED_MEMORY_OBJECTS
    _SC_V6_ILP32_OFF32 = 757,
#define _SC_V6_ILP32_OFF32		_SC_V6_ILP32_OFF32
    _SC_V6_ILP32_OFFBIG = 758,
#define _SC_V6_ILP32_OFFBIG		_SC_V6_ILP32_OFFBIG
    _SC_V6_LP64_OFF64 = 759,
#define _SC_V6_LP64_OFF64		_SC_V6_LP64_OFF64
    _SC_V6_LPBIG_OFFBIG = 760,
#define _SC_V6_LPBIG_OFFBIG		_SC_V6_LPBIG_OFFBIG
    _SC_XOPEN_STREAMS = 761,
#define _SC_XOPEN_STREAMS		_SC_XOPEN_STREAMS /* OpenSolaris */
    _SC_IPV6 = 762,
#define _SC_IPV6			_SC_IPV6
    _SC_RAW_SOCKETS = 763,
#define _SC_RAW_SOCKETS			_SC_RAW_SOCKETS

/* These are found in GNU libc but not OpenSolaris. */

    _SC_EQUIV_CLASS_MAX = 5601,
#define	_SC_EQUIV_CLASS_MAX		_SC_EQUIV_CLASS_MAX
    _SC_CHARCLASS_NAME_MAX,
#define	_SC_CHARCLASS_NAME_MAX		_SC_CHARCLASS_NAME_MAX

    _SC_PII,
#define	_SC_PII				_SC_PII
    _SC_PII_XTI,
#define	_SC_PII_XTI			_SC_PII_XTI
    _SC_PII_SOCKET,
#define	_SC_PII_SOCKET			_SC_PII_SOCKET
    _SC_PII_INTERNET,
#define	_SC_PII_INTERNET		_SC_PII_INTERNET
    _SC_PII_OSI,
#define	_SC_PII_OSI			_SC_PII_OSI
    _SC_POLL,
#define	_SC_POLL			_SC_POLL
    _SC_SELECT,
#define	_SC_SELECT			_SC_SELECT
    _SC_PII_INTERNET_STREAM,
#define	_SC_PII_INTERNET_STREAM		_SC_PII_INTERNET_STREAM
    _SC_PII_INTERNET_DGRAM,
#define	_SC_PII_INTERNET_DGRAM		_SC_PII_INTERNET_DGRAM
    _SC_PII_OSI_COTS,
#define	_SC_PII_OSI_COTS		_SC_PII_OSI_COTS
    _SC_PII_OSI_CLTS,
#define	_SC_PII_OSI_CLTS		_SC_PII_OSI_CLTS
    _SC_PII_OSI_M,
#define	_SC_PII_OSI_M			_SC_PII_OSI_M

    _SC_XOPEN_XPG2,
#define _SC_XOPEN_XPG2			_SC_XOPEN_XPG2
    _SC_XOPEN_XPG3,
#define _SC_XOPEN_XPG3			_SC_XOPEN_XPG3
    _SC_XOPEN_XPG4,
#define _SC_XOPEN_XPG4			_SC_XOPEN_XPG4

    _SC_CHAR_BIT,
#define	_SC_CHAR_BIT			_SC_CHAR_BIT
    _SC_CHAR_MAX,
#define	_SC_CHAR_MAX			_SC_CHAR_MAX
    _SC_CHAR_MIN,
#define	_SC_CHAR_MIN			_SC_CHAR_MIN
    _SC_INT_MAX,
#define	_SC_INT_MAX			_SC_INT_MAX
    _SC_INT_MIN,
#define	_SC_INT_MIN			_SC_INT_MIN
    _SC_LONG_BIT,
#define	_SC_LONG_BIT			_SC_LONG_BIT
    _SC_WORD_BIT,
#define	_SC_WORD_BIT			_SC_WORD_BIT
    _SC_MB_LEN_MAX,
#define	_SC_MB_LEN_MAX			_SC_MB_LEN_MAX
    _SC_NZERO,
#define	_SC_NZERO			_SC_NZERO
    _SC_SSIZE_MAX,
#define	_SC_SSIZE_MAX			_SC_SSIZE_MAX
    _SC_SCHAR_MAX,
#define	_SC_SCHAR_MAX			_SC_SCHAR_MAX
    _SC_SCHAR_MIN,
#define	_SC_SCHAR_MIN			_SC_SCHAR_MIN
    _SC_SHRT_MAX,
#define	_SC_SHRT_MAX			_SC_SHRT_MAX
    _SC_SHRT_MIN,
#define	_SC_SHRT_MIN			_SC_SHRT_MIN
    _SC_UCHAR_MAX,
#define	_SC_UCHAR_MAX			_SC_UCHAR_MAX
    _SC_UINT_MAX,
#define	_SC_UINT_MAX			_SC_UINT_MAX
    _SC_ULONG_MAX,
#define	_SC_ULONG_MAX			_SC_ULONG_MAX
    _SC_USHRT_MAX,
#define	_SC_USHRT_MAX			_SC_USHRT_MAX

    _SC_NL_ARGMAX,
#define	_SC_NL_ARGMAX			_SC_NL_ARGMAX
    _SC_NL_LANGMAX,
#define	_SC_NL_LANGMAX			_SC_NL_LANGMAX
    _SC_NL_MSGMAX,
#define	_SC_NL_MSGMAX			_SC_NL_MSGMAX
    _SC_NL_NMAX,
#define	_SC_NL_NMAX			_SC_NL_NMAX
    _SC_NL_SETMAX,
#define	_SC_NL_SETMAX			_SC_NL_SETMAX
    _SC_NL_TEXTMAX,
#define	_SC_NL_TEXTMAX			_SC_NL_TEXTMAX

    _SC_BASE,
#define _SC_BASE			_SC_BASE
    _SC_C_LANG_SUPPORT,
#define _SC_C_LANG_SUPPORT		_SC_C_LANG_SUPPORT
    _SC_C_LANG_SUPPORT_R,
#define _SC_C_LANG_SUPPORT_R		_SC_C_LANG_SUPPORT_R
    _SC_DEVICE_IO,
#define _SC_DEVICE_IO			_SC_DEVICE_IO
    _SC_DEVICE_SPECIFIC,
#define _SC_DEVICE_SPECIFIC		_SC_DEVICE_SPECIFIC
    _SC_DEVICE_SPECIFIC_R,
#define _SC_DEVICE_SPECIFIC_R		_SC_DEVICE_SPECIFIC_R
    _SC_FD_MGMT,
#define _SC_FD_MGMT			_SC_FD_MGMT
    _SC_FIFO,
#define _SC_FIFO			_SC_FIFO
    _SC_PIPE,
#define _SC_PIPE			_SC_PIPE
    _SC_FILE_ATTRIBUTES,
#define _SC_FILE_ATTRIBUTES		_SC_FILE_ATTRIBUTES
    _SC_FILE_LOCKING,
#define _SC_FILE_LOCKING		_SC_FILE_LOCKING
    _SC_FILE_SYSTEM,
#define _SC_FILE_SYSTEM			_SC_FILE_SYSTEM
    _SC_MULTI_PROCESS,
#define _SC_MULTI_PROCESS		_SC_MULTI_PROCESS
    _SC_SINGLE_PROCESS,
#define _SC_SINGLE_PROCESS		_SC_SINGLE_PROCESS
    _SC_NETWORKING,
#define _SC_NETWORKING			_SC_NETWORKING
    _SC_REGEX_VERSION,
#define _SC_REGEX_VERSION		_SC_REGEX_VERSION
    _SC_SIGNALS,
#define _SC_SIGNALS			_SC_SIGNALS
    _SC_SYSTEM_DATABASE,
#define _SC_SYSTEM_DATABASE		_SC_SYSTEM_DATABASE
    _SC_SYSTEM_DATABASE_R,
#define _SC_SYSTEM_DATABASE_R		_SC_SYSTEM_DATABASE_R
    _SC_USER_GROUPS,
#define _SC_USER_GROUPS			_SC_USER_GROUPS
    _SC_USER_GROUPS_R,
#define _SC_USER_GROUPS_R		_SC_USER_GROUPS_R
    _SC_STREAMS,
#define _SC_STREAMS			_SC_STREAMS

    _SC_LEVEL1_ICACHE_SIZE,
#define _SC_LEVEL1_ICACHE_SIZE		_SC_LEVEL1_ICACHE_SIZE
    _SC_LEVEL1_ICACHE_ASSOC,
#define _SC_LEVEL1_ICACHE_ASSOC		_SC_LEVEL1_ICACHE_ASSOC
    _SC_LEVEL1_ICACHE_LINESIZE,
#define _SC_LEVEL1_ICACHE_LINESIZE	_SC_LEVEL1_ICACHE_LINESIZE
    _SC_LEVEL1_DCACHE_SIZE,
#define _SC_LEVEL1_DCACHE_SIZE		_SC_LEVEL1_DCACHE_SIZE
    _SC_LEVEL1_DCACHE_ASSOC,
#define _SC_LEVEL1_DCACHE_ASSOC		_SC_LEVEL1_DCACHE_ASSOC
    _SC_LEVEL1_DCACHE_LINESIZE,
#define _SC_LEVEL1_DCACHE_LINESIZE	_SC_LEVEL1_DCACHE_LINESIZE
    _SC_LEVEL2_CACHE_SIZE,
#define _SC_LEVEL2_CACHE_SIZE		_SC_LEVEL2_CACHE_SIZE
    _SC_LEVEL2_CACHE_ASSOC,
#define _SC_LEVEL2_CACHE_ASSOC		_SC_LEVEL2_CACHE_ASSOC
    _SC_LEVEL2_CACHE_LINESIZE,
#define _SC_LEVEL2_CACHE_LINESIZE	_SC_LEVEL2_CACHE_LINESIZE
    _SC_LEVEL3_CACHE_SIZE,
#define _SC_LEVEL3_CACHE_SIZE		_SC_LEVEL3_CACHE_SIZE
    _SC_LEVEL3_CACHE_ASSOC,
#define _SC_LEVEL3_CACHE_ASSOC		_SC_LEVEL3_CACHE_ASSOC
    _SC_LEVEL3_CACHE_LINESIZE,
#define _SC_LEVEL3_CACHE_LINESIZE	_SC_LEVEL3_CACHE_LINESIZE
    _SC_LEVEL4_CACHE_SIZE,
#define _SC_LEVEL4_CACHE_SIZE		_SC_LEVEL4_CACHE_SIZE
    _SC_LEVEL4_CACHE_ASSOC,
#define _SC_LEVEL4_CACHE_ASSOC		_SC_LEVEL4_CACHE_ASSOC
    _SC_LEVEL4_CACHE_LINESIZE,
#define _SC_LEVEL4_CACHE_LINESIZE	_SC_LEVEL4_CACHE_LINESIZE
  };

/* Values for the NAME argument to `confstr'.  */
enum
  {
    _CS_PATH = 65,			/* The default search path.  */
#define _CS_PATH		_CS_PATH

    _CS_LFS_CFLAGS = 68,
#define _CS_LFS_CFLAGS	_CS_LFS_CFLAGS
    _CS_LFS_LDFLAGS = 69,
#define _CS_LFS_LDFLAGS	_CS_LFS_LDFLAGS
    _CS_LFS_LIBS = 70,
#define _CS_LFS_LIBS		_CS_LFS_LIBS
    _CS_LFS_LINTFLAGS = 71,
#define _CS_LFS_LINTFLAGS	_CS_LFS_LINTFLAGS
    _CS_LFS64_CFLAGS = 72,
#define _CS_LFS64_CFLAGS	_CS_LFS64_CFLAGS
    _CS_LFS64_LDFLAGS = 73,
#define _CS_LFS64_LDFLAGS	_CS_LFS64_LDFLAGS
    _CS_LFS64_LIBS = 74,
#define _CS_LFS64_LIBS	_CS_LFS64_LIBS
    _CS_LFS64_LINTFLAGS = 75,
#define _CS_LFS64_LINTFLAGS	_CS_LFS64_LINTFLAGS

    _CS_XBS5_ILP32_OFF32_CFLAGS = 700,
#define _CS_XBS5_ILP32_OFF32_CFLAGS _CS_XBS5_ILP32_OFF32_CFLAGS
    _CS_XBS5_ILP32_OFF32_LDFLAGS = 701,
#define _CS_XBS5_ILP32_OFF32_LDFLAGS _CS_XBS5_ILP32_OFF32_LDFLAGS
    _CS_XBS5_ILP32_OFF32_LIBS = 702,
#define _CS_XBS5_ILP32_OFF32_LIBS _CS_XBS5_ILP32_OFF32_LIBS
    _CS_XBS5_ILP32_OFF32_LINTFLAGS = 703,
#define _CS_XBS5_ILP32_OFF32_LINTFLAGS _CS_XBS5_ILP32_OFF32_LINTFLAGS
/* 704 */
    _CS_XBS5_ILP32_OFFBIG_CFLAGS = 705,
#define _CS_XBS5_ILP32_OFFBIG_CFLAGS _CS_XBS5_ILP32_OFFBIG_CFLAGS
    _CS_XBS5_ILP32_OFFBIG_LDFLAGS = 706,
#define _CS_XBS5_ILP32_OFFBIG_LDFLAGS _CS_XBS5_ILP32_OFFBIG_LDFLAGS
    _CS_XBS5_ILP32_OFFBIG_LIBS = 707,
#define _CS_XBS5_ILP32_OFFBIG_LIBS _CS_XBS5_ILP32_OFFBIG_LIBS
    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS = 708,
#define _CS_XBS5_ILP32_OFFBIG_LINTFLAGS _CS_XBS5_ILP32_OFFBIG_LINTFLAGS
    _CS_XBS5_LP64_OFF64_CFLAGS = 709,
#define _CS_XBS5_LP64_OFF64_CFLAGS _CS_XBS5_LP64_OFF64_CFLAGS
    _CS_XBS5_LP64_OFF64_LDFLAGS = 710,
#define _CS_XBS5_LP64_OFF64_LDFLAGS _CS_XBS5_LP64_OFF64_LDFLAGS
    _CS_XBS5_LP64_OFF64_LIBS = 711,
#define _CS_XBS5_LP64_OFF64_LIBS _CS_XBS5_LP64_OFF64_LIBS
    _CS_XBS5_LP64_OFF64_LINTFLAGS = 712,
#define _CS_XBS5_LP64_OFF64_LINTFLAGS _CS_XBS5_LP64_OFF64_LINTFLAGS
    _CS_XBS5_LPBIG_OFFBIG_CFLAGS = 713,
#define _CS_XBS5_LPBIG_OFFBIG_CFLAGS _CS_XBS5_LPBIG_OFFBIG_CFLAGS
    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS = 714,
#define _CS_XBS5_LPBIG_OFFBIG_LDFLAGS _CS_XBS5_LPBIG_OFFBIG_LDFLAGS
    _CS_XBS5_LPBIG_OFFBIG_LIBS = 715,
#define _CS_XBS5_LPBIG_OFFBIG_LIBS _CS_XBS5_LPBIG_OFFBIG_LIBS
    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS = 716,
#define _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS

    _CS_POSIX_V6_ILP32_OFF32_CFLAGS = 800,
#define _CS_POSIX_V6_ILP32_OFF32_CFLAGS _CS_POSIX_V6_ILP32_OFF32_CFLAGS
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS = 801,
#define _CS_POSIX_V6_ILP32_OFF32_LDFLAGS _CS_POSIX_V6_ILP32_OFF32_LDFLAGS
    _CS_POSIX_V6_ILP32_OFF32_LIBS = 802,
#define _CS_POSIX_V6_ILP32_OFF32_LIBS _CS_POSIX_V6_ILP32_OFF32_LIBS
    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS = 803,
#define _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS = 804,
#define _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS = 805,
#define _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS = 806,
#define _CS_POSIX_V6_ILP32_OFFBIG_LIBS _CS_POSIX_V6_ILP32_OFFBIG_LIBS
    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS = 807,
#define _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS
    _CS_POSIX_V6_LP64_OFF64_CFLAGS = 808,
#define _CS_POSIX_V6_LP64_OFF64_CFLAGS _CS_POSIX_V6_LP64_OFF64_CFLAGS
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS = 809,
#define _CS_POSIX_V6_LP64_OFF64_LDFLAGS _CS_POSIX_V6_LP64_OFF64_LDFLAGS
    _CS_POSIX_V6_LP64_OFF64_LIBS = 810,
#define _CS_POSIX_V6_LP64_OFF64_LIBS _CS_POSIX_V6_LP64_OFF64_LIBS
    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS = 811,
#define _CS_POSIX_V6_LP64_OFF64_LINTFLAGS _CS_POSIX_V6_LP64_OFF64_LINTFLAGS
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS = 812,
#define _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS = 813,
#define _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS = 814,
#define _CS_POSIX_V6_LPBIG_OFFBIG_LIBS _CS_POSIX_V6_LPBIG_OFFBIG_LIBS
    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS = 815,
#define _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS
    _CS_V6_WIDTH_RESTRICTED_ENVS = 816,
#define _CS_V6_WIDTH_RESTRICTED_ENVS	_CS_V6_WIDTH_RESTRICTED_ENVS
#define _CS_POSIX_V6_WIDTH_RESTRICTED_ENVS	_CS_V6_WIDTH_RESTRICTED_ENVS

/* These are found in GNU libc but not OpenSolaris. */

    _CS_GNU_LIBC_VERSION = 5701,
#define _CS_GNU_LIBC_VERSION	_CS_GNU_LIBC_VERSION
    _CS_GNU_LIBPTHREAD_VERSION
#define _CS_GNU_LIBPTHREAD_VERSION	_CS_GNU_LIBPTHREAD_VERSION
  };