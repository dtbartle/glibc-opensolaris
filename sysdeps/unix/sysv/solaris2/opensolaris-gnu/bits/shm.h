/* Copyright (C) 1995, 1996, 1997, 2000, 2002, 2004, 2008
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

#ifndef _SYS_SHM_H
# error "Never include <bits/shm.h> directly; use <sys/shm.h> instead."
#endif

#include <bits/types.h>
#include <bits/wordsize.h>

/* Permission flag for shmget.  */
#define SHM_R		0400		/* or S_IRUGO from <linux/stat.h> */
#define SHM_W		0200		/* or S_IWUGO from <linux/stat.h> */

/* Flags for `shmat'.  */
#define SHM_RDONLY		010000		/* attach read-only else read-write */
#define SHM_RND			020000		/* round attach address to SHMLBA */
#define SHM_REMAP		040000		/* take-over region on attach */
#define SHM_PAGEABLE	0100000		/*pageable ISM */

/* Commands for `shmctl'.  */
#define SHM_LOCK	3		/* lock segment (root only) */
#define SHM_UNLOCK	4		/* unlock segment (root only) */

__BEGIN_DECLS

/* Segment low boundary address multiple.  */
#define SHMLBA		(__getpagesize ())
extern int __getpagesize (void) __THROW __attribute__ ((__const__));


/* Type to count number of attaches.  */
typedef unsigned long int shmatt_t;

/* Data structure describing a set of semaphores.  */
struct shmid_ds
  {
    struct ipc_perm shm_perm;	/* operation permission struct */
    size_t shm_segsz;			/* size of segment in bytes */
    void *shm_amp;				/* segment anon_map pointer */
    unsigned short shm_lkcnt;	/* number of times it is being locked */
    __pid_t shm_cpid;			/* pid of creator */
    __pid_t shm_lpid;			/* pid of last shmop */
    shmatt_t shm_nattch;		/* number of current attaches */
    unsigned long shm_cnattch;	/* number of ISM attaches */
    __time_t shm_atime;			/* time of last shmat() */
#if __WORDSIZE == 32
	int32_t shm_pad1;
#endif
    __time_t shm_dtime;			/* time of last shmdt() */
#if __WORDSIZE == 32
	int32_t shm_pad2;
#endif
    __time_t shm_ctime;			/* time of last change by shmctl() */
#if __WORDSIZE == 32
	int32_t shm_pad3;
    int32_t shm_pad4[4];
#endif
  };

__END_DECLS
