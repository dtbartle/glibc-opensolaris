/* Copyright (C) 1995, 1996, 1997, 1998, 2008
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

#ifndef _SYS_SEM_H
# error "Never include <bits/sem.h> directly; use <sys/sem.h> instead."
#endif

#include <sys/types.h>

#define SEM_A	0200
#define SEM_R	0400

/* Flags for `semop'.  */
#define SEM_UNDO	010000		/* undo the operation on exit */

/* Commands for `semctl'.  */
#define GETNCNT		3		/* get semncnt */
#define GETPID		4		/* get sempid */
#define GETVAL		5		/* get semval */
#define GETALL		6		/* get all semval's */
#define GETZCNT		7		/* get semzcnt */
#define SETVAL		8		/* set semval */
#define SETALL		9		/* set all semval's */


/* Data structure describing a set of semaphores.  */
struct semid_ds
{
  struct ipc_perm sem_perm;		/* operation permission struct */
  struct sem *sem_base;			/* ptr to first semaphore in set */
  unsigned short sem_nsems;		/* number of semaphores in set */
  __time_t sem_otime;			/* last semop() time */
#if __WORDSIZE == 32
  int32_t sem_pad1;
#endif
  __time_t sem_ctime;			/* last time changed by semctl() */
#if __WORDSIZE == 32
  int32_t sem_pad2;
#endif
  int sem_binary;				/* flag indicating semaphore type */
  long sem_pad3[3];
};

/* The user should define a union like the following to use it for arguments
   for `semctl'.

   union semun
   {
     int val;				<= value for SETVAL
     struct semid_ds *buf;		<= buffer for IPC_STAT & IPC_SET
     unsigned short int *array;		<= array for GETALL & SETALL
     struct seminfo *__buf;		<= buffer for IPC_INFO
   };

   Previous versions of this file used to define this union but this is
   incorrect.  One can test the macro _SEM_SEMUN_UNDEFINED to see whether
   one must define the union or not.  */
#define _SEM_SEMUN_UNDEFINED	1
