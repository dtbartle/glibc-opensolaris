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

#ifndef _THREAD_H
#define _THREAD_H

typedef unsigned int thread_t;
typedef unsigned int thread_key_t;

#define THR_BOUND		0x00000001 /* PTHREAD_SCOPE_SYSTEM; unused */
#define THR_NEW_LWP		0x00000002 /* unused */
#define THR_DETACHED	0x00000040 /* PTHREAD_CREATE_DETACHED */
#define THR_SUSPENDED	0x00000080
#define THR_DAEMON		0x00000100

__BEGIN_DECLS

extern int thr_create (void *, size_t, void *(*)(void *), void *, long,
    thread_t *);

extern int thr_join (thread_t, thread_t *, void **);

extern int thr_setconcurrency (int);

extern int thr_getconcurrency (void);

extern void thr_exit (void *);

extern thread_t thr_self (void);

extern int thr_main (void);

extern int thr_kill (thread_t, int);

extern int thr_suspend (thread_t);

extern int thr_continue (thread_t);

extern void thr_yield (void);

extern int thr_setprio (thread_t, int);

extern int thr_getprio (thread_t, int *);

extern int thr_keycreate (thread_key_t *, void(*)(void *));

extern int thr_keycreate_once (thread_key_t *, void(*)(void *));

extern int thr_setspecific (thread_key_t, void *);

extern int thr_getspecific (thread_key_t, void **);

extern int thr_sigsetmask (int how, const sigset_t *set, sigset_t *oset);

__END_DECLS

#endif /* _THREAD_H */
