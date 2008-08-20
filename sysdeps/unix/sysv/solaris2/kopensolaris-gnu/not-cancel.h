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

#include <inline-syscall.h>
#include <sys/types.h>

DECLARE_INLINE_SYSCALL (int, close, int fd);
DECLARE_INLINE_SYSCALL (int, close_nc_ns, int fd);
DECLARE_INLINE_SYSCALL (ssize_t, read, int fd, void *buf, size_t nbytes);
DECLARE_INLINE_SYSCALL (ssize_t, write, int fd, const void *buf,
    size_t nbytes);
DECLARE_INLINE_SYSCALL (ssize_t, writev_nc_ns, int fd,
    const struct iovec *vector, int count);
DECLARE_INLINE_SYSCALL (int, pause, void);
DECLARE_INLINE_SYSCALL (int, nanosleep, const struct timespec *req,
    struct timespec *rem);
DECLARE_INLINE_SYSCALL (int, sigsuspend, const sigset_t *mask);

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
    INLINE_SYSCALL (close, 1, (fd))
#define close_not_cancel_no_status(fd) \
    (void)({ INLINE_SYSCALL (close_nc_ns, 1, (fd)); })

#define read_not_cancel(fd, buf, n) \
    INLINE_SYSCALL (read, 3, (fd), (buf), (n))
#define write_not_cancel(fd, buf, n) \
    INLINE_SYSCALL (write, 3, (fd), (buf), (n))

#define writev_not_cancel_no_status(fd, iov, n) \
    (void)({ INLINE_SYSCALL (writev_nc_ns, 3, (fd), (iov), (n)); })

extern int __fcntl_not_cancel (int fd, int cmd, ...);
#define fcntl_not_cancel(fd, cmd, val) \
    __fcntl_not_cancel (fd, cmd, val)

extern __pid_t __waitpid_not_cancel(__pid_t pid, int *stat_loc, int options);
#define waitpid_not_cancel(pid, stat_loc, options) \
    __waitpid_not_cancel (pid, stat_loc, options)

# define pause_not_cancel() \
    INLINE_SYSCALL (pause, 0)

# define nanosleep_not_cancel(requested_time, remaining) \
    INLINE_SYSCALL (nanosleep, 2, (requested_time), (remaining))

#define sigsuspend_not_cancel(set) \
    INLINE_SYSCALL (sigsuspend, 1, (set))
