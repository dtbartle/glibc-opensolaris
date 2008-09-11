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

#ifndef _SYS_PROC_H
#define _SYS_PROC_H

#define SSLEEP	1
#define SRUN	2
#define SZOMB	3
#define SSTOP	4
#define SIDL	5
#define SONPROC	6
#define SWAIT	7

#define SSYS		0x00000001
#define SEXITING	0x00000002
#define SITBUSY		0x00000004
#define SFORKING	0x00000008
#define SWATCHOK	0x00000010
#define SKILLED		0x00000100
#define SSCONT		0x00000200
#define SZONETOP	0x00000400
#define SEXTKILLED	0x00000800
#define SUGID		0x00002000
#define SEXECED		0x00004000
#define SJCTL		0x00010000
#define SNOWAIT		0x00020000
#define SVFORK		0x00040000
#define SVFWAIT		0x00080000
#define SEXITLWPS	0x00100000
#define SHOLDFORK	0x00200000
#define SHOLDFORK1	0x00800000
#define SCOREDUMP	0x01000000
#define SMSACCT		0x02000000
#define SLWPWRAP	0x04000000
#define SAUTOLPG	0x08000000
#define SNOCD		0x10000000
#define SHOLDWATCH	0x20000000
#define SMSFORK		0x40000000
#define SDOCORE		0x80000000

#endif /* _SYS_PROC_H */
