#
# additional routines and headers for libc
#
ifeq ($(subdir),csu)
sysdep_routines += errno-loc
endif
ifeq ($(subdir),io)
sysdep_routines += sys_open sys_open64 sys_openat sys_openat64 \
    sys_fstat sys_fstat64 sys_fstatat sys_fstatat64 sys_lstat \
    sys_lstat64 sys_stat sys_stat64 sys_sendfilev sys_sendfilev64 \
    sys_pollsys sys_getcwd sys_read sys_write sys_pipe sys_close \
    sys_close_nc_ns sys_chdir sys_fchdir
endif
ifeq ($(subdir),misc)
sysdep_routines +=  gethrtime mount umount umount2 systeminfo resolvepath \
    getpagesizes memcntl meminfo uadmin getpflags setpflags issetugid ucred \
    priv processor_bind processor_info p_online pset_create pset_destroy \
    pset_assign pset_info pset_bind pset_getloadavg pset_list pset_setattr \
    pset_getattr swapctl
sysdep_routines += sys_fdsync sys_sysconfig sys_brk sys_fcntl sys_utssys \
    sys_writev sys_writev_nc_ns sys_lwp_private sys_uname sys_getloadavg \
    sys_utimes sys_getpeerucred sys_ucred_get sys_privsys sys_syslabeling \
    sys_putmsg sys_putpmsg sys_meminfo sys_pset_getloadavg
sysdep_headers += sys/feature_tests.h sys/lwp.h sys/mount.h sys/cred.h \
    sys/systeminfo.h sys/uadmin.h sys/utssys.h sys/fstyp.h sys/fsid.h \
    sys/priocntl.h sys/procset.h sys/ptyvar.h sys/stream.h sys/synch.h \
    sys/sockio.h sys/ioccom.h sys/tty.h sys/trap.h sys/sysconfig.h \
	sys/ptms.h sys/stack.h sys/regset.h sys/fault.h sys/processor.h \
    sys/pset.h sys/priv.h sys/acl.h sys/procfs.h sys/reg.h
sysdep_headers += ucred.h priv.h bits/regset.h
endif
ifeq ($(subdir),dirent)
sysdep_routines += sys_getdents sys_getdents64
endif
ifeq ($(subdir),posix)
sysdep_routines += sys_nanosleep sys_pause exit-thread sched_priv
endif
ifeq ($(subdir),resource)
sysdep_routines += priocntl getvmusage
sysdep_routines += sys_rusagesys sys_priocntlsys
endif
ifeq ($(subdir),rt)
sysdep_routines += sys_yield
endif
ifeq ($(subdir),signal)
sysdep_routines += sys_lwp_sigmask sys_sigqueue sys_sigtimedwait \
    sys_sigaction
endif
ifeq ($(subdir),socket)
sysdep_routines += sa_len sys_so_socket sys_so_socketpair sys_send \
    sys_sendmsg sys_sendto sys_accept sys_bind \
    sys_connect sys_getpeername sys_getsockname sys_getsockopt \
    sys_setsockopt sys_shutdown sys_recvmsg sys_listen
sysdep_routines += netmask
endif
ifeq ($(subdir),string)
sysdep_routines += strlcpy strlcat
endif
ifeq ($(subdir),time)
sysdep_routines += ntp_adjtime ntp_gettime sys_time sys_stime
sysdep_headers += sys/timex.h
endif

#
# Additional sysdeps for ld.so
#
ifeq ($(subdir),elf)
sysdep-rtld-routines += sys_sysconfig
endif

#
# some files inclue getaddrinfo.c directly, which uses close_not_cancel_nc_ns
#
ifeq ($(subdir),nscd)
nscd-modules += sys_close_nc_ns
endif

ifeq ($(subdir),nptl)
libpthread-sysdep_routines += sys_fcntl sys_send sys_sendmsg sys_sendto \
    sys_accept sys_connect sys_recvmsg sys_fdsync sys_open sys_open64 \
    sys_close_nc_ns sys_sigaction sys_priocntlsys sched_priv priocntl
endif
