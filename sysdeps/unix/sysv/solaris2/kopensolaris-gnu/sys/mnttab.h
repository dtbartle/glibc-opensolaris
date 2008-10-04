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

#ifndef _SYS_MNTTAB_H
#define _SYS_MNTTAB_H

#include <features.h>
#include <paths.h>

#ifndef __USE_SUN
# include <mntent.h>
#else

# define MNTTAB	_PATH_MOUNTED
# define MNT_LINE_MAX	1024

# define MNT_TOOLONG	1
# define MNT_TOOMANY	2
# define MNT_TOOFEW	3

# define mntnull(mp)	((mp)->mnt_special = (mp)->mnt_mountp = \
	(mp)->mnt_fstype = (mp)->mnt_mntopts = (mp)->mnt_time = NULL)
# define putmntent(fd, mp)	(-1)

struct mnttab
  {
	char *mnt_special;
	char *mnt_mountp;
	char *mnt_fstype;
	char *mnt_mntopts;
	char *mnt_time;
  };

/*
 * NOTE: fields in extmnttab should match struct mnttab till new fields
 * are encountered, this allows hasmntopt to work properly when its arg is
 * a pointer to an extmnttab struct cast to a mnttab struct pointer.
 */
struct extmnttab
  {
	char *mnt_special;
	char *mnt_mountp;
	char *mnt_fstype;
	char *mnt_mntopts;
	char *mnt_time;
	unsigned int mnt_major;
	unsigned int mnt_minor;
  };

__BEGIN_DECLS

extern void	resetmnttab (FILE *);
extern int	getmntent (FILE *, struct mnttab *);
extern int	getextmntent (FILE *, struct extmnttab *, size_t);
extern int	getmntany (FILE *, struct mnttab *, struct mnttab *);
extern char	*hasmntopt (struct mnttab *, char *);
extern char	*mntopt (char **);

__END_DECLS

#endif /* __USE_SUN */

#endif /* _SYS_MNTTAB_H */
