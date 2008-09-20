/* The `struct utmp' type, describing entries in the utmp file.  GNU version.
   Copyright (C) 1993, 1996, 1997, 1998, 1999, 2002
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

#ifndef _UTMP_H
# error "Never include <bits/utmp.h> directly; use <utmp.h> instead."
#endif

#include <paths.h>
#include <sys/time.h>
#include <sys/types.h>
#include <bits/wordsize.h>
#include <sys/types32.h>


#define UT_LINESIZE	12
#define UT_NAMESIZE	8
#define UT_HOSTSIZE	257


/* The structure describing an entry in the database of
   previous logins.  */
struct lastlog
  {
#if __WORDSIZE == 64 && defined __WORDSIZE_COMPAT32
    int32_t ll_time;
#else
    __time_t ll_time;
#endif
    char ll_line[UT_LINESIZE];
    char ll_host[UT_HOSTSIZE];
  };


/* The structure describing the status of a terminated process.  This
   type is used in `struct utmp' below.  */
struct exit_status
  {
    short int e_termination;	/* Process termination status.  */
    short int e_exit;		/* Process exit status.  */
  };


/* The structure describing an entry in the user accounting database.  */
struct utmp
{
  char ut_user[UT_NAMESIZE];	/* Username.  */
  char ut_id[4];		/* Inittab ID.  */
  char ut_line[UT_LINESIZE];	/* Devicename.  */
  short int ut_pid;			/* Process ID of login process.  */
  short int ut_type;		/* Type of login.  */
  struct exit_status ut_exit;	/* Exit status of a process marked
				   as DEAD_PROCESS.  */
  time_t ut_time;  /* Time entry was made.  */
};

/* Backwards compatibility hacks.  */
#define ut_name		ut_user

#define NONROOT_USR	2
#define nonuser(ut)	((ut).ut_exit.e_exit == NONROOT_USR ? 1 : 0)
#define setuser(ut)	((ut).ut_exit.e_exit = NONROOT_USR)


/* Values for the `ut_type' field of a `struct utmp'.  */
#define EMPTY		0	/* No valid user accounting information.  */
#define RUN_LVL		1	/* The system's runlevel.  */
#define BOOT_TIME	2	/* Time of system boot.  */
#define NEW_TIME	3	/* Time after system clock changed.  */
#define OLD_TIME	4	/* Time when system clock changed.  */
#define INIT_PROCESS	5	/* Process spawned by the init process.  */
#define LOGIN_PROCESS	6	/* Session leader of a logged in user.  */
#define USER_PROCESS	7	/* Normal process.  */
#define DEAD_PROCESS	8	/* Terminated process.  */

#define ACCOUNTING	9
#define DOWN_TIME	10
#define UTMAXTYPE	DOWN_TIME

#define RUNLVL_MSG	"run-level %c"
#define BOOT_MSG	"system boot"
#define OTIME_MSG	"old time"
#define NTIME_MSG	"new time"
#define PSRADM_MSG	"%03d  %s"
#define DOWN_MSG	"system down"

struct futmp
  {
  char ut_user[UT_NAMESIZE];	/* Username.  */
  char ut_id[4];		/* Inittab ID.  */
  char ut_line[UT_LINESIZE];	/* Devicename.  */
  int16_t ut_pid;			/* Process ID of login process.  */
  int16_t ut_type;		/* Type of login.  */
  struct
    {
      int16_t e_termination;
      int16_t e_exit;
    };	/* Exit status of a process marked
				   as DEAD_PROCESS.  */
  time32_t ut_time;  /* Time entry was made.  */
};


/* Tell the user that we have a modern system with UT_HOST, UT_PID,
   UT_TYPE, UT_ID and UT_TV fields.  */
#define _HAVE_UT_TYPE	1
#define _HAVE_UT_PID	1
#define _HAVE_UT_ID	1
