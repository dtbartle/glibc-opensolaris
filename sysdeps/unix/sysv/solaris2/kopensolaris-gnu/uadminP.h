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

#ifndef _UADMINP_H
#define _UADMINP_H

/* uadmin cmd's.  */
#define	A_REBOOT	1
#define	A_SHUTDOWN	2
#define	A_FREEZE	3
#define	A_REMOUNT	4
#define	A_DUMP		5
#define	A_FTRACE	15
#define	A_SWAPCTL	16

/* Shutdown-related fcn's.  */
#define	AD_HALT		0
#define	AD_BOOT		1
#define	AD_IBOOT	2
#define	AD_SBOOT	3
#define	AD_SIBOOT	4
#define	AD_POWEROFF	6
#define	AD_NOSYNC	7

#endif /* _UADMINP_H */
