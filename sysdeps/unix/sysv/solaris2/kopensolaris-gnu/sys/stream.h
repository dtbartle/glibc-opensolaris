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

#ifndef _SYS_STREAM_H
#define _SYS_STREAM_H

#include <sys/types.h>
#include <sys/cred.h>

#define	M_DATA		0x00
#define	M_PROTO		0x01
#define	M_MULTIDATA	0x02

#define	M_BREAK		0x08
#define	M_PASSFP	0x09
#define	M_EVENT		0x0a
#define	M_SIG		0x0b
#define	M_DELAY		0x0c
#define	M_CTL		0x0d
#define	M_IOCTL		0x0e
#define	M_SETOPTS	0x10
#define	M_RSE		0x11

#define	M_IOCACK	0x81
#define	M_IOCNAK	0x82
#define	M_PCPROTO	0x83
#define	M_PCSIG		0x84
#define	M_READ		0x85
#define	M_FLUSH		0x86
#define	M_STOP		0x87
#define	M_START		0x88
#define	M_HANGUP	0x89
#define	M_ERROR		0x8a
#define	M_COPYIN	0x8b
#define	M_COPYOUT	0x8c
#define	M_IOCDATA	0x8d
#define	M_PCRSE		0x8e
#define	M_STOPI		0x8f
#define	M_STARTI	0x90
#define	M_PCEVENT	0x91
#define	M_UNHANGUP	0x92

struct iocblk
  {
    int ioc_cmd;
    cred_t *ioc_cr;
    unsigned int ioc_id;
#if __WORDSIZE == 32
    size_t ioc_count;
    int ioc_error;
    int ioc_rval;
    int ioc_fill1;
    unsigned int ioc_flag;
    int ioc_filler[2];
#else
    unsigned int ioc_flag;
    size_t ioc_count;
    int ioc_rval;
    int ioc_error;
#endif
  };

typedef struct iocblk *IOCP;

#endif /* _SYS_STREAM_H */
