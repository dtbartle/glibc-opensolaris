/* Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_UTSSYS_H
#define _SYS_UTSSYS_H

#include <sys/types.h>

#define UTS_UNAME	0x00
#define	UTS_USTAT	0x02
#define	UTS_FUSERS	0x03

/* UTS_FUSERS flags.  */
#define F_FILE_ONLY	0x01
#define F_CONTAINED	0x02
#define F_NBMANDLIST	0x04
#define F_DEVINFO	0x08
#define F_KINFO_COUNT	0x10

typedef struct f_user
  {
	int fu_flags;   /* see below */
	union
	  {
		struct
		  {
			pid_t u_pid;
            uid_t u_uid;
		  } u_info;
        struct
		  {
			int k_modid;
			int k_instance;
			int k_minor;
		  } k_info;
	  } fu_info;
  } f_user_t;

#define fu_pid		fu_info.u_info.u_pid
#define fu_uid		fu_info.u_info.u_uid
#define fu_modid	fu_info.k_info.k_modid
#define fu_instance	fu_info.k_info.k_instance
#define fu_minor	fu_info.k_info.k_minor

/* fu_flags values.  */
#define F_CDIR		0x01
#define F_RDIR		0x02
#define F_TEXT		0x04
#define F_MAP		0x08
#define F_OPEN		0x10
#define F_TRACE		0x20
#define F_TTY		0x40
#define F_NBM		0x80
#define F_KERNEL	0x80000000

typedef struct fu_data
  {
	int fud_user_max;
	int fud_user_count;
	struct f_user fud_user[1];
  } fu_data_t;

#define fu_data_size(x) (sizeof(fu_data_t) - sizeof(f_user_t) + \
	((x) * sizeof(f_user_t)))

#endif /* _SYS_UTSSYS_H */
