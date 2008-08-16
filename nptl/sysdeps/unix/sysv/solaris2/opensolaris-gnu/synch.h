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

#ifndef _SYNCH_H
#define _SYNCH_H

#include <sys/synch.h>
#include <features.h>

typedef lwp_mutex_t mutex_t;

typedef lwp_cond_t cond_t;

typedef lwp_rwlock_t rwlock_t;

typedef lwp_sema_t sema_t;

__BEGIN_DECLS

/* condition variables */

int	cond_init(cond_t *, int, void *);

int	cond_destroy(cond_t *);

int	cond_wait(cond_t *, mutex_t *);

int	cond_timedwait(cond_t *, mutex_t *, struct timespec *);

int	cond_reltimedwait(cond_t *, mutex_t *, struct timespec *);

int	cond_signal(cond_t *);

int	cond_broadcast(cond_t *);

/* mutexes */

int	mutex_init(mutex_t *, int, void *);

int	mutex_destroy(mutex_t *);

int	mutex_consistent(mutex_t *);

int	mutex_lock(mutex_t *);

int	mutex_trylock(mutex_t *);

int	mutex_unlock(mutex_t *);

/* reader/writer locks */

int	rwlock_init(rwlock_t *, int, void *);

int	rwlock_destroy(rwlock_t *);

int	rw_rdlock(rwlock_t *);

int	rw_wrlock(rwlock_t *);

int	rw_unlock(rwlock_t *);

int	rw_tryrdlock(rwlock_t *);

int	rw_trywrlock(rwlock_t *);

/* semaphores */

int	sema_init(sema_t *, unsigned int, int, void *);

int	sema_destroy(sema_t *);

int	sema_wait(sema_t *);

int	sema_timedwait(sema_t *, struct timespec *);

int	sema_reltimedwait(sema_t *, const struct timespec *);

int	sema_post(sema_t *);

int	sema_trywait(sema_t *);

__END_DECLS

#endif /* _SYNCH_H */
