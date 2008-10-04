/* Copyright (C) 1992,1993,1995-2000,2002-2006,2007,2008
	Free Software Foundation, Inc.
   This file is part of the GNU C Library.
   Contributed by Ulrich Drepper, <drepper@gnu.org>, August 1995.
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

#ifndef _OPENSOLARIS_I386_SYSDEP_H
#define _OPENSOLARIS_I386_SYSDEP_H 1

#define DECLARE_INLINE_SYSCALL(ret, name, args...) \
    extern ret __syscall_##name (args)

/* There is some commonality.  */
#include <sysdeps/unix/i386/sysdep.h>
#include <bp-sym.h>
#include <bp-asm.h>
#include <syscallP.h>

/* XXX: This needs to come before #include <tls.h>.  */

/* Pointer mangling support.  */
#if defined NOT_IN_libc && defined IS_IN_rtld
/* We cannot use the thread descriptor because in ld.so we use setjmp
   earlier than the descriptor is initialized.  Using a global variable
   is too complicated here since we have no PC-relative addressing mode.  */
#else
# ifdef __ASSEMBLER__
#  define PTR_MANGLE(reg)   xorl %gs:POINTER_GUARD, reg;              \
                roll $9, reg
#  define PTR_DEMANGLE(reg) rorl $9, reg;                     \
                xorl %gs:POINTER_GUARD, reg
# else
#  define PTR_MANGLE(var)   asm ("xorl %%gs:%c2, %0\n"            \
                     "roll $9, %0"                \
                     : "=r" (var)                 \
                     : "0" (var),                 \
                       "i" (offsetof (tcbhead_t,          \
                              pointer_guard)))
#  define PTR_DEMANGLE(var) asm ("rorl $9, %0\n"                  \
                     "xorl %%gs:%c2, %0"              \
                     : "=r" (var)                 \
                     : "0" (var),                 \
                       "i" (offsetof (tcbhead_t,          \
                              pointer_guard)))
# endif
#endif


/* Defines RTLD_PRIVATE_ERRNO and USE_DL_SYSINFO.  */
#include <dl-sysdep.h>
#include <tls.h>

/* It's too much trouble to pull in all of errno.h just for this */
#ifndef ERESTART
# define ERESTART   91  /* Restartable system call.  */
# define EINTR		4	/* Interrupted system call.  */
#endif

#ifdef __ASSEMBLER__

/* This is needed so that we know when to set %edx to -1 on error.  */
#ifdef SYSCALL_64BIT_RETURN
# define SYSCALL_64BIT_RETURN_ASM   orl $-1, %edx;
#else
# define SYSCALL_64BIT_RETURN_ASM
#endif

#ifdef SYSCALL_RESTARTABLE
# define DO_RESTART \
    cmpl $ERESTART, %eax; \
    je L(restart);
#else
# define DO_RESTART
#endif

/* We don't want the label for the error handle to be global when we define
   it here.  */
#ifdef PIC
# define SYSCALL_ERROR_LABEL 0f
#else
# define SYSCALL_ERROR_LABEL syscall_error
#endif

#undef  PSEUDO
#define PSEUDO(name, syscall_name, args)                      \
  .text;                                      \
  ENTRY (name)                                    \
  L(restart):                                       \
    DO_CALL (syscall_name, args);                         \
    jnb 2f;										\
    DO_RESTART                             \
    jmp SYSCALL_ERROR_LABEL;                           \
2:                                              \
  L(pseudo_end):

#define	PSEUDO_SUBCALL(name, syscall_name, subcall_name, args)				      \
  .text;                                      \
  ENTRY (name)                                    \
    movl 0(%esp), %ecx;                               \
    movl %ecx, -4(%esp);							\
    addl $-4, %esp; \
    movl $SYS_ify (SUB_##subcall_name), 4(%esp);							\
  L(restart):                                       \
    DO_CALL (syscall_name, args);                         \
    jnb 2f;										\
    DO_RESTART                             \
    movl %ecx, 4(%esp);							\
    addl $4, %esp; \
    jmp SYSCALL_ERROR_LABEL;                           \
2:											\
    movl %ecx, 4(%esp);							\
    addl $4, %esp; \
  L(pseudo_end):

#undef  PSEUDO_END
#define PSEUDO_END(name)                              \
  SYSCALL_ERROR_HANDLER                               \
  END (name)

#undef  PSEUDO_NOERRNO
#define PSEUDO_NOERRNO(name, syscall_name, args)                  \
  .text;                                      \
  ENTRY (name)                                    \
    DO_CALL (syscall_name, args)

#define	PSEUDO_SUBCALL_NOERRNO(name, syscall_name, subcall_name, args)	      \
  .text;                                      \
  ENTRY (name)                                    \
    movl 0(%esp), %ecx;                               \
    movl %ecx, -4(%esp);							\
    addl $-4, %esp; \
    movl $SYS_ify (SUB_##subcall_name), 4(%esp);							\
    DO_CALL (syscall_name, args);                         \
    movl %ecx, 4(%esp);							\
    addl $4, %esp;

#undef  PSEUDO_END_NOERRNO
#define PSEUDO_END_NOERRNO(name)                          \
  END (name)

#define ret_NOERRNO ret

/* The function has to return the error code.  */
#undef  PSEUDO_ERRVAL
#define PSEUDO_ERRVAL(name, syscall_name, args) \
  .text;                                      \
  ENTRY (name)                                    \
    DO_CALL (syscall_name, args);                         \
    jnb 1f;										\
    cmpl $ERESTART, %eax;                   \
    jne 2f;                        \
    movl $EINTR, %eax;                  \
    jmp 2f;                             \
1:  xorl %eax, %eax;                        \
2:;

#define PSEUDO_SUBCALL_ERRVAL(name, syscall_name, subcall_name, args)         \
  .text;                                      \
  ENTRY (name)                                    \
    movl 0(%esp), %ecx;                               \
    movl %ecx, -4(%esp);							\
    addl $-4, %esp; \
    movl $SYS_ify (SUB_##subcall_name), 4(%esp);							\
  L(restart):                                       \
    DO_CALL (syscall_name, args);                         \
    jnb 1f;										\
    cmpl $ERESTART, %eax;                   \
    jne 2f;                                      \
    movl $EINTR, %eax;                  \
    jmp 2f;                             \
1:  xorl %eax, %eax;                        \
2:											\
    movl %ecx, 4(%esp);                 \
    addl $4, %esp;


#undef  PSEUDO_END_ERRVAL
#define PSEUDO_END_ERRVAL(name) \
  END (name)

#define ret_ERRVAL ret

#undef  PSEUDO_FASTTRAP
#define PSEUDO_FASTTRAP(name, trap_name, args)                \
  .text;                                      \
  ENTRY (name)                                    \
    movl $T_##trap_name, %eax;                 \
    int $T_FASTTRAP;                    \
  L(pseudo_end):


#ifndef PIC
# define SYSCALL_ERROR_HANDLER  /* Nothing here; code in sysdep.S is used.  */
#else

# if RTLD_PRIVATE_ERRNO
#  define SYSCALL_ERROR_HANDLER                           \
0: SETUP_PIC_REG(cx);                                  \
  addl $_GLOBAL_OFFSET_TABLE_, %ecx;                          \
  movl %eax, rtld_errno@GOTOFF(%ecx);                         \
  orl $-1, %eax;                                  \
  SYSCALL_64BIT_RETURN_ASM                      \
  jmp L(pseudo_end);

# elif defined _LIBC_REENTRANT

#  if USE___THREAD
#   ifndef NOT_IN_libc
#    define SYSCALL_ERROR_ERRNO __libc_errno
#   else
#    define SYSCALL_ERROR_ERRNO errno
#   endif
#   define SYSCALL_ERROR_HANDLER                          \
0: SETUP_PIC_REG (cx);                                 \
  addl $_GLOBAL_OFFSET_TABLE_, %ecx;                          \
  movl SYSCALL_ERROR_ERRNO@GOTNTPOFF(%ecx), %ecx;                 \
  SYSCALL_ERROR_HANDLER_TLS_STORE (%eax, %ecx);                   \
  orl $-1, %eax;                                  \
  SYSCALL_64BIT_RETURN_ASM                      \
  jmp L(pseudo_end);
#   ifndef NO_TLS_DIRECT_SEG_REFS
#    define SYSCALL_ERROR_HANDLER_TLS_STORE(src, destoff)             \
  movl src, %gs:(destoff)
#   else
#    define SYSCALL_ERROR_HANDLER_TLS_STORE(src, destoff)             \
  addl %gs:0, destoff;                                \
  movl src, (destoff)
#   endif
#  else
#   define SYSCALL_ERROR_HANDLER                          \
0:pushl %ebx;                                     \
  cfi_adjust_cfa_offset (4);                                                  \
  cfi_rel_offset (ebx, 0);                                                    \
  SETUP_PIC_REG (bx);                                 \
  addl $_GLOBAL_OFFSET_TABLE_, %ebx;                          \
  pushl %eax;                                     \
  cfi_adjust_cfa_offset (4);                                                  \
  PUSH_ERRNO_LOCATION_RETURN;                             \
  call BP_SYM (__errno_location)@PLT;                         \
  POP_ERRNO_LOCATION_RETURN;                              \
  popl %ecx;                                      \
  cfi_adjust_cfa_offset (-4);                                                 \
  popl %ebx;                                      \
  cfi_adjust_cfa_offset (-4);                                                 \
  cfi_restore (ebx);                                                          \
  movl %ecx, (%eax);                                  \
  orl $-1, %eax;                                  \
  SYSCALL_64BIT_RETURN_ASM                      \
  jmp L(pseudo_end);
/* A quick note: it is assumed that the call to `__errno_location' does
   not modify the stack!  */
#  endif
# else
/* Store (%eax) into errno through the GOT.  */
#  define SYSCALL_ERROR_HANDLER                           \
0:SETUP_PIC_REG(cx);                                  \
  addl $_GLOBAL_OFFSET_TABLE_, %ecx;                          \
  movl errno@GOT(%ecx), %ecx;                             \
  movl %eax, (%ecx);                                  \
  orl $-1, %eax;                                  \
  SYSCALL_64BIT_RETURN_ASM                      \
  jmp L(pseudo_end);
# endif /* _LIBC_REENTRANT */
#endif  /* PIC */

/* TODO: use sysenter instead of int */
#undef  DO_CALL
#define DO_CALL(syscall_name, args)                           \
    movl $SYS_ify (syscall_name), %eax;                       \
    int $0x91

#else   /* !__ASSEMBLER__ */

/* Consistency check for position-independent code.  */
#ifdef __PIC__
# define check_consistency()                              \
  ({ int __res;                                   \
     __asm__ __volatile__                             \
       ("call __i686.get_pc_thunk.cx;"                        \
    "addl $_GLOBAL_OFFSET_TABLE_, %%ecx;"                     \
    "subl %%ebx, %%ecx;"                              \
    "je 1f;"                                  \
    "ud2;"                                    \
    "1:\n"                                    \
    ".section .gnu.linkonce.t.__i686.get_pc_thunk.cx,\"ax\",@progbits;"   \
    ".globl __i686.get_pc_thunk.cx;"                      \
    ".hidden __i686.get_pc_thunk.cx;"                     \
    ".type __i686.get_pc_thunk.cx,@function;"                 \
    "__i686.get_pc_thunk.cx:"                         \
    "movl (%%esp), %%ecx;"                            \
    "ret;"                                    \
    ".previous"                               \
    : "=c" (__res));                              \
     __res; })
#endif

/* TODO: This is a terrible implementation of INTERNAL_SYSCALL.  */

/* Some NPTL code calls these macros.  */
# include <errno.h>
# define INTERNAL_SYSCALL(name, err, nr, args...) __internal_##name##_##nr (&(err), args)
# define INTERNAL_SYSCALL_DECL(err) int err = 0;
# define INTERNAL_SYSCALL_ERROR_P(val, err) (err != 0)
# define INTERNAL_SYSCALL_ERRNO(val, err) (err)

#endif /* __ASSEMBLER__ */

#endif /* _OPENSOLARIS_I386_SYSDEP_H */
