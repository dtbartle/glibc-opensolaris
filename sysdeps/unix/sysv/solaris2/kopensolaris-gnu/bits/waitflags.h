/* Definitions of flag bits for `waitpid' et al.
   Copyright (C) 1992, 1996-1997, 2000, 2002, 2008
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

#if !defined _SYS_WAIT_H && !defined _STDLIB_H
# error "Never include <bits/waitflags.h> directly; use <sys/wait.h> instead."
#endif


/* Bits in the third argument to `waitpid'.  */
#define	WNOHANG		0x40	/* Don't block waiting.  */
#define	WUNTRACED	0x04	/* Report status of stopped children.  */

/* Bits in the fourth argument to `waitid'.  */
#define	WSTOPPED	WUNTRACED	/* Report stopped child (same as WUNTRACED). */
#define	WCONTINUED	0x08	/* Report continued child.  */
#define WNOWAIT		0x80	/* Don't reap, just poll status. */
#define WEXITED		0x01	/* Report dead child. */
#define WTRAPPED	0x02    /* Report processes stopped while tracing */
