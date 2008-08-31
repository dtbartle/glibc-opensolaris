/* Uncancelable versions of cancelable interfaces.  OpenSolaris version.
   Copyright (C) 2003, 2006, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by David Bartley <dtbartle@csclub.uwaterloo.ca>.

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

#include <sys/syscall.h>
#include <sys/types.h>

extern int open_not_cancel(const char *name, int flags, mode_t mode);
#define open_not_cancel_2(name, flags) \
    open_not_cancel((name), (flags), 0)

extern int open64_not_cancel(const char *name, int flags, mode_t mode);
#define open64_not_cancel_2(name, flags) \
    open64_not_cancel((name), (flags), 0)

extern int openat_not_cancel(int dirfd, const char *name,
    int flags, mode_t mode);
#define openat_not_cancel_3(fd, name, flags) \
    openat_not_cancel((fd), (name), (flags), 0)

extern int openat64_not_cancel(int dirfd, const char *name,
    int flags, mode_t mode);
#define openat64_not_cancel_3(fd, name, flags) \
    openat64_not_cancel((fd), (name), (flags), 0)

#define close_not_cancel(fd) \
    syscall (SYS_close, fd)
#define close_not_cancel_no_status(fd) \
    ({sysret_t __ret; \
    (void)__systemcall (&__ret, SYS_close, (fd));})

#define read_not_cancel(fd, buf, n) \
    syscall (SYS_read, (fd), (buf), (n))
#define write_not_cancel(fd, buf, n) \
    syscall (SYS_write, (fd), (buf), (n))

#define writev_not_cancel_no_status(fd, iov, n) \
    ({sysret_t __ret; \
    (void)__systemcall (&__ret, SYS_writev, (fd), (iov), (n));})

extern int __fcntl_not_cancel (int fd, int cmd, ...);
#define fcntl_not_cancel(fd, cmd, val) \
    __fcntl_not_cancel ((fd), (cmd), (val))

extern __pid_t __waitpid_not_cancel(__pid_t pid, int *stat_loc, int options);
#define waitpid_not_cancel(pid, stat_loc, options) \
    __waitpid_not_cancel ((pid), (stat_loc), (options))

# define pause_not_cancel() \
    syscall (SYS_pause)

# define nanosleep_not_cancel(requested_time, remaining) \
    syscall (SYS_nanosleep, (requested_time), (remaining))

#define sigsuspend_not_cancel(set) \
    syscall (SYS_sigsuspend, (set))

#define waitid_not_cancel(idtype, id, infop, options) \
    syscall (SYS_waitid, (idtype), (id), (infop), (options))
