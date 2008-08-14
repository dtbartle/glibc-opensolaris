/* Definition for thread-local data handling.  OpenSolaris/i386 version.
   Copyright (C) 2002, 2003, 2004, 2008 Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   OpenSolaris bits contributed by David Bartley
    <dtbartle@csclub.uwaterloo.ca>, 2008.

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

#ifndef _TLS_H
#define _TLS_H 1

# include <dl-sysdep.h>

/* Additional descr fields.  */
# define PLATFORM_DESCR_FIELDS \
    int sigpipe_disabled;

/* __thread doesn't work for statically-linked executables.  */
#if !defined (SHARED)
# undef HAVE___THREAD
#endif

#ifndef __ASSEMBLER__
# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>
# include <stdlib.h>
# include <atomic.h>

/* Type for the dtv.  */
typedef union dtv
{
  size_t counter;
  struct
  {
    void *val;
    bool is_static;
  } pointer;
} dtv_t;


/* Type of the TCB.  */
typedef struct
{
  void *tcb;			/* Points to this structure.  */
  dtv_t *dtv;			/* Vector of pointers to TLS data.  */
  void *self;			/* Pointer to the thread descriptor.  */
  int multiple_threads;
  uintptr_t sysinfo;
  uintptr_t stack_guard;
  uintptr_t pointer_guard;
  int gscope_flag;
} tcbhead_t;

#else /* __ASSEMBLER__ */
# include <tcb-offsets.h>
#endif

/* We require TLS support in the tools.  */
#ifndef HAVE_TLS_SUPPORT
# error "TLS support is required."
#endif

/* Signal that TLS support is available.  */
#define USE_TLS	1

#ifndef __ASSEMBLER__
/* Get system call information.  */
# include <sysdep.h>

/* Get the thread descriptor definition.  */
# include <descr.h>

/* This is the size of the initial TCB.  */
# define TLS_INIT_TCB_SIZE sizeof (tcbhead_t)

/* Alignment requirements for the initial TCB.  */
# define TLS_INIT_TCB_ALIGN __alignof__ (tcbhead_t)

/* This is the size of the TCB.  */
# define TLS_TCB_SIZE sizeof (struct pthread)

/* Alignment requirements for the TCB.  */
# define TLS_TCB_ALIGN __alignof__ (struct pthread)

/* The TCB can have any size and the memory following the address the
   thread pointer points to is unspecified.  Allocate the TCB there.  */
# define TLS_TCB_AT_TP	1

/* Install the dtv pointer.  The pointer passed is to the element with
   index -1 which contain the length.  */
# define INSTALL_DTV(descr, dtvp) \
  ((tcbhead_t *) (descr))->dtv = (dtvp) + 1

/* Return the address of the dtv for the current thread.  */
# define THREAD_DTV() \
  ({ struct pthread *__descr;				      \
     THREAD_GETMEM (__descr, header.dtv); })

/* Return the thread descriptor for the current thread.

   The contained asm must *not* be marked volatile since otherwise
   assignments like
        pthread_descr self = thread_self();
   do not get optimized away.  */
# define THREAD_SELF \
  ({ struct pthread *__self;						      \
     asm ("movl %%gs:%c1,%0" : "=r" (__self)				      \
	  : "i" (offsetof (struct pthread, header.self)));		      \
     __self;})

/* Read member of the thread descriptor directly.  */
# define THREAD_GETMEM(descr, member) \
  ({ __typeof (descr->member) __value;					      \
     if (sizeof (__value) == 1)						      \
       asm volatile ("movb %%gs:%P2,%b0"				      \
		     : "=q" (__value)					      \
		     : "0" (0), "i" (offsetof (struct pthread, member)));     \
     else if (sizeof (__value) == 4)					      \
       asm volatile ("movl %%gs:%P1,%0"					      \
		     : "=r" (__value)					      \
		     : "i" (offsetof (struct pthread, member)));	      \
     else								      \
       {								      \
	 if (sizeof (__value) != 8)					      \
	   /* There should not be any value with a size other than 1,	      \
	      4 or 8.  */						      \
	   abort ();							      \
									      \
	 asm volatile ("movl %%gs:%P1,%%eax\n\t"			      \
		       "movl %%gs:%P2,%%edx"				      \
		       : "=A" (__value)					      \
		       : "i" (offsetof (struct pthread, member)),	      \
			 "i" (offsetof (struct pthread, member) + 4));	      \
       }								      \
     __value; })


/* Same as THREAD_GETMEM, but the member offset can be non-constant.  */
# define THREAD_GETMEM_NC(descr, member, idx) \
  ({ __typeof (descr->member[0]) __value;				      \
     if (sizeof (__value) == 1)						      \
       asm volatile ("movb %%gs:%P2(%3),%b0"				      \
		     : "=q" (__value)					      \
		     : "0" (0), "i" (offsetof (struct pthread, member[0])),   \
		     "r" (idx));					      \
     else if (sizeof (__value) == 4)					      \
       asm volatile ("movl %%gs:%P1(,%2,4),%0"				      \
		     : "=r" (__value)					      \
		     : "i" (offsetof (struct pthread, member[0])),	      \
		       "r" (idx));					      \
     else								      \
       {								      \
	 if (sizeof (__value) != 8)					      \
	   /* There should not be any value with a size other than 1,	      \
	      4 or 8.  */						      \
	   abort ();							      \
									      \
	 asm volatile  ("movl %%gs:%P1(,%2,8),%%eax\n\t"		      \
			"movl %%gs:4+%P1(,%2,8),%%edx"			      \
			: "=&A" (__value)				      \
			: "i" (offsetof (struct pthread, member[0])),	      \
			  "r" (idx));					      \
       }								      \
     __value; })


/* Same as THREAD_SETMEM, but the member offset can be non-constant.  */
# define THREAD_SETMEM(descr, member, value) \
  ({ if (sizeof (descr->member) == 1)					      \
       asm volatile ("movb %b0,%%gs:%P1" :				      \
		     : "iq" (value),					      \
		       "i" (offsetof (struct pthread, member)));	      \
     else if (sizeof (descr->member) == 4)				      \
       asm volatile ("movl %0,%%gs:%P1" :				      \
		     : "ir" (value),					      \
		       "i" (offsetof (struct pthread, member)));	      \
     else								      \
       {								      \
	 if (sizeof (descr->member) != 8)				      \
	   /* There should not be any value with a size other than 1,	      \
	      4 or 8.  */						      \
	   abort ();							      \
									      \
	 asm volatile ("movl %%eax,%%gs:%P1\n\t"			      \
		       "movl %%edx,%%gs:%P2" :				      \
		       : "A" (value),					      \
			 "i" (offsetof (struct pthread, member)),	      \
			 "i" (offsetof (struct pthread, member) + 4));	      \
       }})


/* Set member of the thread descriptor directly.  */
# define THREAD_SETMEM_NC(descr, member, idx, value) \
  ({ if (sizeof (descr->member[0]) == 1)				      \
       asm volatile ("movb %b0,%%gs:%P1(%2)" :				      \
		     : "iq" (value),					      \
		       "i" (offsetof (struct pthread, member)),		      \
		       "r" (idx));					      \
     else if (sizeof (descr->member[0]) == 4)				      \
       asm volatile ("movl %0,%%gs:%P1(,%2,4)" :			      \
		     : "ir" (value),					      \
		       "i" (offsetof (struct pthread, member)),		      \
		       "r" (idx));					      \
     else								      \
       {								      \
	 if (sizeof (descr->member[0]) != 8)				      \
	   /* There should not be any value with a size other than 1,	      \
	      4 or 8.  */						      \
	   abort ();							      \
									      \
	 asm volatile ("movl %%eax,%%gs:%P1(,%2,8)\n\t"			      \
		       "movl %%edx,%%gs:4+%P1(,%2,8)" :			      \
		       : "A" (value),					      \
			 "i" (offsetof (struct pthread, member)),	      \
			 "r" (idx));					      \
       }})

#define LOCK_PREFIX "lock;"

/* Atomic compare and exchange on TLS, returning old value.  */
#define THREAD_ATOMIC_CMPXCHG_VAL(descr, member, newval, oldval) \
  ({ __typeof (descr->member) __ret;					      \
     __typeof (oldval) __old = (oldval);				      \
     if (sizeof (descr->member) == 4)					      \
       asm volatile (LOCK_PREFIX "cmpxchgl %2, %%gs:%P3"		      \
		     : "=a" (__ret)					      \
		     : "0" (__old), "r" (newval),			      \
		       "i" (offsetof (struct pthread, member)));	      \
     else								      \
       /* Not necessary for other sizes in the moment.  */		      \
       abort ();							      \
     __ret; })


/* Atomic set bit.  */
#define THREAD_ATOMIC_BIT_SET(descr, member, bit) \
  (void) ({ if (sizeof ((descr)->member) == 4)				      \
	      asm volatile (LOCK_PREFIX "orl %1, %%gs:%P0"		      \
			    :: "i" (offsetof (struct pthread, member)),	      \
			       "ir" (1 << (bit)));			      \
	    else							      \
	      /* Not necessary for other sizes in the moment.  */	      \
	      abort (); })


/* Install new dtv for current thread.  */
# define INSTALL_NEW_DTV(dtv) \
  ({ struct pthread *__descr;				      \
     THREAD_SETMEM (__descr, header.dtv, (dtv)); })

/* Return dtv of given thread descriptor.  */
# define GET_DTV(descr) \
  (((tcbhead_t *) (descr))->dtv)

# ifdef __PIC__
#  define TLS_EBX_ARG "r"
#  define TLS_LOAD_EBX "xchgl %3, %%ebx\n\t"
# else
#  define TLS_EBX_ARG "b"
#  define TLS_LOAD_EBX
# endif

# if defined NEED_DL_SYSINFO
#  define INIT_SYSINFO \
     head->sysinfo = GLRO(dl_sysinfo)
# else
#  define INIT_SYSINFO
# endif

/* Code to initially initialize the thread pointer.  This might need
   special attention since 'errno' is not yet available and if the
   operation can cause a failure 'errno' must not be touched. */

/* solaris2 has lwp_private in order to set the thread data */
# include <sys/lwp.h>
# include <inline-syscall.h>

# define TLS_SETUP_GS_SEGMENT(descr, secondcall)     \
  ({        \
    DECLARE_INLINE_SYSCALL (int, lwp_private, int cmd, int which,       \
        uintptr_t base);                \
    (INLINE_SYSCALL (lwp_private, 3, _LWP_SETPRIVATE, _LWP_GSBASE,       \
        (uintptr_t)descr) == -1)            \
        ? "lwp_private failed when setting up thread-local storage\n" : NULL;   \
  })

/*   The value of this macro is null if successful, or an error string.  */

# define TLS_INIT_TP(descr, secondcall)				      \
  ({									      \
    void *_descr = (descr);						      \
    tcbhead_t *head = _descr;						      \
									      \
    head->tcb = _descr;							      \
    /* For now the thread descriptor is at the same address.  */	      \
    head->self = _descr;						      \
									      \
    INIT_SYSINFO;							      \
    TLS_SETUP_GS_SEGMENT (_descr, secondcall);      \
  })

/* Set the stack guard field in TCB head.  */
# define THREAD_SET_STACK_GUARD(value) \
  THREAD_SETMEM (THREAD_SELF, header.stack_guard, value)
# define THREAD_COPY_STACK_GUARD(descr) \
  ((descr)->header.stack_guard				      \
   = THREAD_GETMEM (THREAD_SELF, header.stack_guard))

/* Set the pointer guard field in the TCB head.  */
# define THREAD_SET_POINTER_GUARD(value) \
  THREAD_SETMEM (THREAD_SELF, header.pointer_guard, value)
# define THREAD_COPY_POINTER_GUARD(descr) \
  ((descr)->header.pointer_guard				      \
   = THREAD_GETMEM (THREAD_SELF, header.pointer_guard))

/* Get and set the global scope generation counter in the TCB head.  */
#define THREAD_GSCOPE_FLAG_UNUSED 0
#define THREAD_GSCOPE_FLAG_USED   1
#define THREAD_GSCOPE_RESET_FLAG() \
  do                                          \
    { int __res;                                  \
      asm volatile ("xchgl %0, %%gs:%P1"                      \
            : "=r" (__res)                        \
            : "i" (offsetof (struct pthread, header.gscope_flag)),    \
              "0" (THREAD_GSCOPE_FLAG_UNUSED));               \
    }                                         \
  while (0)
#define THREAD_GSCOPE_SET_FLAG() \
  THREAD_SETMEM (THREAD_SELF, header.gscope_flag, THREAD_GSCOPE_FLAG_USED)
#define THREAD_GSCOPE_WAIT() \
  GL(dl_wait_lookup_done) ()

# endif /* __ASSEMBLER__ */

#endif /* _TLS_H */
