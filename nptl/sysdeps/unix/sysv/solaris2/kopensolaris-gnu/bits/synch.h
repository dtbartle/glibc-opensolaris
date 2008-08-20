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

#include <bits/types.h>

#if (defined __need_pthread_bits  && !defined __pthread_bits_defined) || \
    (defined __need_synch_bits  && !defined __synch_bits_defined)

# ifdef __need_pthread_bits
typedef struct
# else
typedef struct _lwp_mutex
# endif
{
	struct {
		uint16_t	flag1;
		uint8_t		flag2;
		uint8_t		ceiling;
		union {
			uint16_t bcptype;
			struct {
				uint8_t	count_type1;
				uint8_t	count_type2;
			} mtype_rcount;
		} mbcp_type_un;
		uint16_t	magic;
	} flags;
	union {
		struct {
			uint8_t	pad[8];
		} lock64;
		struct {
			uint32_t ownerpid;
			uint32_t lockword;
		} lock32;
		uint64_t owner64;
	} lock;
	uint64_t data;
# ifdef __need_pthread_bits
} pthread_mutex_t;
# else
} lwp_mutex_t;
# endif

# ifdef __need_pthread_bits
typedef struct
# else
typedef struct _lwp_cond
# endif
{
	struct {
		uint8_t		flag[4];
		uint16_t	type;
		uint16_t	magic;
	} flags;
	uint64_t data;
# ifdef __need_pthread_bits
} pthread_cond_t;
# else
} lwp_cond_t;
# endif

#endif /* defined __need_pthread_bits  && !defined ... */

#if (defined __need_pthread_bits  && (defined __USE_UNIX98 || \
    defined __USE_XOPEN2K) && !defined __pthread_bits_defined) || \
    (defined __need_synch_bits && !defined __synch_bits_defined)

# ifdef __need_pthread_bits
typedef struct
# else
typedef struct _lwp_rwlock
# endif
{
	int32_t readers;
	uint16_t type;
	uint16_t magic;
# ifdef __need_pthread_bits
	pthread_mutex_t mutex;
	pthread_cond_t readercv;
	pthread_cond_t writercv;
# else
	lwp_mutex_t mutex;
	lwp_cond_t readercv;
	lwp_cond_t writercv;
# endif
/* XXX: These are non-standard additions (see NOTES.opensolaris).  */
    uint64_t owner;
	uint32_t ownerpid;
	uint32_t pad;
# ifdef __need_pthread_bits
} pthread_rwlock_t;
# else
} lwp_rwlock_t;
# endif

#endif /* defined __need_pthread_bits && !defined ... */

#if (defined __need_semaphore_bits && !defined __semaphore_bits_defined) || \
    (defined __need_synch_bits && !defined __synch_bits_defined)

#ifdef __need_semaphore_bits
typedef struct
#else
typedef struct _lwp_sema
#endif
{
	uint32_t	count;
	uint16_t	type;
	uint16_t	magic;
	uint8_t		flags[8];
	uint64_t	data;
#ifdef __need_semaphore_bits
} sem_t;
#else
} lwp_sema_t;
#endif

#endif /* defined __need_semaphore_bits && !defined ... */

#ifdef __need_pthread_bits
# undef __need_pthread_bits
# define __pthread_bits_defined
#endif
#ifdef __need_semaphore_bits
# undef __need_semaphore_bits
# define __semaphore_bits_defined
#endif
#ifdef __need_synch_bits
# undef __need_synch_bits
# define __synch_bits_defined
#endif
