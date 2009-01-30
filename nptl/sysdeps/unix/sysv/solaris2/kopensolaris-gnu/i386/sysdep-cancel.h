/* Copyright (C) 2002, 2003, 2004, 2005, 2006, 2008
    Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Jakub Jelinek <jakub@redhat.com>, 2002.

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

#include <sysdep.h>
#include <tls.h>
#ifndef __ASSEMBLER__
# include <pthreadP.h>
#endif

/* XXX: We don't support _NOERRNO or _ERRVAL varietites.  */
#undef PSEUDO_ERRNO
#undef PSEUDO_SUBCALL_NOERRNO
#undef PSEUDO_ERRVAL
#undef PSEUDO_SUBCALL_NOERRNO

/* This is needed so that we don't clobber %edx in the cancellation calls.  */
#ifdef SYSCALL_64BIT_RETURN
# define SYSCALL_64BIT_PUSH_ASM     pushl %edx; cfi_adjust_cfa_offset (4);
# define SYSCALL_64BIT_POP_ASM      popl %edx; cfi_adjust_cfa_offset (-4);
#else
# define SYSCALL_64BIT_PUSH_ASM
# define SYSCALL_64BIT_POP_ASM
#endif

#ifdef SYSCALL_RESTARTABLE
# define DO_RESTART_CANCEL \
    cmpl $ERESTART, %eax; \
    je L(restart_cancel);
#else
# define DO_RESTART_CANCEL
#endif

#if !defined NOT_IN_libc || defined IS_IN_libpthread || defined IS_IN_librt

/* Note that CDISABLE is an internal function, so we need to
   pass-by-register (we pass the argument in %eax).  */

# undef  PSEUDO
# define PSEUDO(name, syscall_name, args)                      \
  .text;                                      \
  ENTRY (name)                                    \
    cmpl $0, %gs:MULTIPLE_THREADS_OFFSET;				      \
    jne L(pseudo_cancel);						      \
  .type __##syscall_name##_nocancel,@function;				      \
  .globl __##syscall_name##_nocancel;					      \
  __##syscall_name##_nocancel:						      \
  L(restart):                                       \
    DO_CALL (syscall_name, args);                         \
    jnb 2f;										\
    DO_RESTART                             \
    jmp SYSCALL_ERROR_LABEL;                           \
2:  ret;                                            \
  .size __##syscall_name##_nocancel,.-__##syscall_name##_nocancel;	      \
  L(pseudo_cancel):							      \
  L(restart_cancel):                                       \
    CENABLE;								      \
    movl %eax, %ecx;                    \
    DO_CALL (syscall_name, args);                         \
    jnb 3f;										\
    DO_RESTART_CANCEL                             \
    pushl %eax; cfi_adjust_cfa_offset (4);  \
    SYSCALL_64BIT_PUSH_ASM                  \
    movl %ecx, %eax;                        \
    CDISABLE;                           \
    SYSCALL_64BIT_POP_ASM                     \
    popl %eax; cfi_adjust_cfa_offset (-4);    \
    jmp SYSCALL_ERROR_LABEL;                           \
3:                                                  \
    pushl %eax; cfi_adjust_cfa_offset (4);  \
    SYSCALL_64BIT_PUSH_ASM                  \
    movl %ecx, %eax;                        \
    CDISABLE;                           \
    SYSCALL_64BIT_POP_ASM                     \
    popl %eax; cfi_adjust_cfa_offset (-4);    \
  L(pseudo_end):

/* XXX: This uses %edx, so subcalls that return 64-bit ints won't work.  */
# undef  PSEUDO_SUBCALL
# define PSEUDO_SUBCALL(name, syscall_name, subcall_name, args)				      \
  .text;                                      \
  ENTRY (name)                                    \
    cmpl $0, %gs:MULTIPLE_THREADS_OFFSET;				      \
    jne L(pseudo_cancel);						      \
  .type __##subcall_name##_nocancel,@function;				      \
  .globl __##subcall_name##_nocancel;					      \
  __##subcall_name##_nocancel:						      \
    movl 0(%esp), %ecx;                               \
    movl %ecx, -4(%esp);							\
    addl $-4, %esp;                             \
    movl $SYS_ify (SUB_##subcall_name), 4(%esp);							\
  L(restart):                                       \
    DO_CALL (syscall_name, args);                         \
    jnb 2f;										\
    DO_RESTART                             \
    movl %ecx, 4(%esp);							\
    addl $-4, %esp;                             \
    jmp SYSCALL_ERROR_LABEL;                           \
2:											\
    addl $4, %esp;                                     \
    movl %ecx, 0(%esp);							\
    ret;                                            \
  .size __##subcall_name##_nocancel,.-__##subcall_name##_nocancel;	      \
  L(pseudo_cancel):							      \
    CENABLE;								      \
    movl %eax, %ecx;                    \
    movl 0(%esp), %edx;                               \
    movl %edx, -4(%esp);			\
    addl $-4, %esp;                             \
    movl $SYS_ify (SUB_##subcall_name), 4(%esp);							\
  L(restart_cancel):                                       \
    DO_CALL (syscall_name, args);                         \
    jnb 3f;										\
    DO_RESTART_CANCEL                             \
    pushl %eax; cfi_adjust_cfa_offset (4);  \
    SYSCALL_64BIT_PUSH_ASM                  \
    movl %ecx, %eax;                        \
    CDISABLE;                           \
    SYSCALL_64BIT_POP_ASM                     \
    popl %eax; cfi_adjust_cfa_offset (-4);    \
    movl 0(%esp), %ecx;                               \
    movl %ecx, 4(%esp);							\
    addl $4, %esp;                          \
    jmp SYSCALL_ERROR_LABEL;                           \
3:											\
    pushl %eax; cfi_adjust_cfa_offset (4);  \
    SYSCALL_64BIT_PUSH_ASM                  \
    movl %ecx, %eax;                        \
    CDISABLE;                           \
    SYSCALL_64BIT_POP_ASM                     \
    popl %eax; cfi_adjust_cfa_offset (-4);    \
    movl 0(%esp), %ecx;                               \
    movl %ecx, 4(%esp);							\
    addl $4, %esp;                          \
  L(pseudo_end):


# define SAVE_OLDTYPE	movl %eax, %ecx;
# ifdef IS_IN_libpthread
#  define CENABLE	call __pthread_enable_asynccancel;
#  define CDISABLE	call __pthread_disable_asynccancel
# elif !defined NOT_IN_libc
#  define CENABLE	call __libc_enable_asynccancel;
#  define CDISABLE	call __libc_disable_asynccancel
# elif defined IS_IN_librt
#  define CENABLE	call __librt_enable_asynccancel;
#  define CDISABLE	call __librt_disable_asynccancel
# else
#  error Unsupported library
# endif

# ifndef __ASSEMBLER__
#  define SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
				   header.multiple_threads) == 0, 1)
# else
#  define SINGLE_THREAD_P cmpl $0, %gs:MULTIPLE_THREADS_OFFSET
# endif

#elif !defined __ASSEMBLER__

# define SINGLE_THREAD_P (1)
# define NO_CANCELLATION 1

#endif

#ifndef __ASSEMBLER__
# define RTLD_SINGLE_THREAD_P \
  __builtin_expect (THREAD_GETMEM (THREAD_SELF, \
				   header.multiple_threads) == 0, 1)
#endif
