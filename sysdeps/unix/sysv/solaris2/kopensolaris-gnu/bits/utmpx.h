/* Structures and definitions for the user accounting database.
    OpenSolaris version.
   Copyright (C) 1997, 1998, 2000, 2001, 2002, 2008
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

#ifndef _UTMPX_H
# error "Never include <bits/utmpx.h> directly; use <utmpx.h> instead."
#endif

#include <bits/types.h>
#include <sys/time.h>
#include <bits/wordsize.h>


#ifdef __USE_GNU
# include <paths.h>
# define _PATH_UTMPX	_PATH_UTMP
# define _PATH_WTMPX	_PATH_WTMP
#endif


#define __UT_LINESIZE	32
#define __UT_NAMESIZE	32
#define __UT_HOSTSIZE	256


/* The structure describing the status of a terminated process.  This
   type is used in `struct utmpx' below.  */
struct __exit_status
  {
#ifdef __USE_MISC
    short int e_termination;	/* Process termination status.  */
    short int e_exit;		/* Process exit status.  */
#else
    short int __e_termination;	/* Process termination status.  */
    short int __e_exit;		/* Process exit status.  */
#endif
  };


/* The structure describing an entry in the user accounting database.  */
struct utmpx
{
  char ut_user[__UT_NAMESIZE];	/* Username.  */
  char ut_id[4];		/* Inittab ID. */
  char ut_line[__UT_LINESIZE];	/* Devicename.  */
  __pid_t ut_pid;		/* Process ID of login process.  */
  short int ut_type;		/* Type of login.  */
  struct __exit_status ut_exit;	/* Exit status of a process marked
				   as DEAD_PROCESS.  */
  struct timeval ut_tv;		/* Time entry was made.  */
  int ut_session;		/* Session ID, used for windowing.  */
  int __pad[5];
  short ut_syslen;
  char ut_host[__UT_HOSTSIZE];	/* Hostname for remote login.  */
};


/* Values for the `ut_type' field of a `struct utmpx'.  */
#define EMPTY		0	/* No valid user accounting information.  */

#ifdef __USE_GNU
# define RUN_LVL	1	/* The system's runlevel.  */
#endif
#define BOOT_TIME	2	/* Time of system boot.  */
#define NEW_TIME	3	/* Time after system clock changed.  */
#define OLD_TIME	4	/* Time when system clock changed.  */

#define INIT_PROCESS	5	/* Process spawned by the init process.  */
#define LOGIN_PROCESS	6	/* Session leader of a logged in user.  */
#define USER_PROCESS	7	/* Normal process.  */
#define DEAD_PROCESS	8	/* Terminated process.  */

#ifdef __USE_MISC
# define ACCOUNTING	9	/* System accounting.  */
# define DOWN_TIME	10
# define  UTMAXTYPE	DOWN_TIME
#endif

#define UTMPX_FILE	"/var/adm/utmpx"
#define WTMPX_FILE	"/var/adm/wtmpx"
