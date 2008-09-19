/* Copyright (C) 1996, 1997, 2008 Free Software Foundation, Inc.
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


#if !defined _SYS_UIO_H && !defined _FCNTL_H
# error "Never include <bits/uio.h> directly; use <sys/uio.h> instead."
#endif

#ifndef _BITS_UIO_H
#define _BITS_UIO_H	1

#include <bits/types.h>
#include <features.h>

/* Maximum number of iovec's that can be processed in a single call. */
#define UIO_MAXIOV	16

/* `struct iovec' -- Structure describing a section of memory.  */

struct iovec {
  /* Starting address.  */
  __ptr_t iov_base;
  /* Length in bytes.  */
  size_t iov_len;
};

typedef struct iovec iovec_t;

#ifdef __USE_MISC

typedef enum uio_seg
  {
	UIO_USERSPACE,
	UIO_SYSSPACE,
	UIO_USERISPACE
  } uio_seg_t;

typedef struct uio
  {
	iovec_t *uio_iov;
	int uio_iovcnt;
	lloff_t _uio_offset;
	uio_seg_t uio_segflg;
	__uint16_t uio_fmode;
	__uint16_t uio_extflg;
	lloff_t _uio_limit;
	ssize_t uio_resid;
  } uio_t;

#endif

#endif /* _SYS_UIO_H */
