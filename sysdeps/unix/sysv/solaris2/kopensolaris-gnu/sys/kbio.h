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

#ifndef _SYS_KBIO_H
#define _SYS_KBIO_H

#define KIOC		('k'<<8)

#if defined(__i386__)
# define KIOCTRANS	(KIOC|30)
# define KIOCSETKEY	(KIOC|31)
# define KIOCGETKEY	(KIOC|32)
# define KIOCGTRANS	(KIOC|35)
# define KIOCTRANSABLE	(KIOC|36)
# define KIOCGTRANSABLE	(KIOC|37)
# define KIOCGDIRECT	(KIOC|41)
# define KIOCSKEY	(KIOC|42)
#else
# define KIOCTRANS	(KIOC|0)
# define KIOCSETKEY	(KIOC|1)
# define KIOCGETKEY	(KIOC|2)
# define KIOCGTRANS	(KIOC|5)
# define KIOCTRANSABLE	(KIOC|6)
# define KIOCGTRANSABLE	(KIOC|7)
# define KIOCGDIRECT	(KIOC|11)
# define KIOCSKEY	(KIOC|12)
#endif

#define KIOCCMD		(KIOC|8)
#define KIOCTYPE	(KIOC|9)
#define KIOCSDIRECT	(KIOC|10)
#define KIOCGKEY	(KIOC|13)
#define KIOCSLED	(KIOC|14)
#define KIOCGLED	(KIOC|15)
#define KIOCSCOMPAT	(KIOC|16)
#define KIOCGCOMPAT	(KIOC|17)
#define KIOCSLAYOUT	(KIOC|19)
#define KIOCLAYOUT	(KIOC|20)
#define KIOCSKABORTEN	(KIOC|21)
#define KIOCGRPTDELAY	(KIOC|22)
#define KIOCSRPTDELAY	(KIOC|23)
#define KIOCGRPTRATE	(KIOC|24)
#define KIOCSRPTRATE	(KIOC|25)
#define KIOCSETFREQ	(KIOC|26)
#define KIOCMKTONE	(KIOC|27)

#define TR_CANNOT	0
#define TR_CAN		1

struct	kiockey
  {
	int kio_tablemask;
	unsigned char kio_station;
	unsigned char kio_entry;
	char kio_string[10];
  };

#define KIOCABORT1	-1
#define KIOCABORT2	-2
#define KIOCABORT1A	-3


struct kiockeymap
  {
	int kio_tablemask;
	unsigned char kio_station;
	unsigned short kio_entry;
	char kio_string[10];
  };

#define KIOCABORTDISABLE	0
#define KIOCABORTENABLE		1
#define KIOCABORTALTERNATE	2

enum fr_beep_type
  {
	CONSOLE_BEEP = 1,
	KBD_BEEP = 2
  };

struct freq_request
  {
	enum fr_beep_type type;
	int16_t freq;
  };

#define PIT_HZ		1193182

#define KDMKTONE	KIOCMKTONE

#define KIOCRPTDELAY_MIN	(100)
#define KIOCRPTRATE_MIN		(1)

#endif /* _SYS_KBIO_H */
