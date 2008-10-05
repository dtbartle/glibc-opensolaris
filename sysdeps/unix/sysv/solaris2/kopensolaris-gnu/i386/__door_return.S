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

#include <sysdep.h>
#include "door-offsets.h"

/* The door_return call serves two purposes. First, it is called to transfer
   the results of a door server back to the client. Second, it waits for a
   client to pass in results destined for the server. The first part involves
   no tricks; we simply call into the kernel. When the syscall returns, our
   stack will have been adjusted; client args will have been copied onto the
   stack. The stack pointer itself points to a struct door_results.

   For the second part, we need to pass the door results to the server
   function. The first few fields of door_results matches the arguments of
   the server function (probably by design) so we can just call the server
   function. */

ENTRY (__door_return)
L(restart):
    DO_CALL (door, 6)

    /* Check for error.  */
    jb SYSCALL_ERROR_LABEL;

    /* TODO: adjust cfi.  */

    /* Call server function.  */
    movl oDOOR_RESULTS_PC(%esp), %eax
    call *%eax

    /* The server function is supposed to call door_return...  */
    pushl $0
    call __pthread_exit
L(pseudo_end):
PSEUDO_END (__door_return)
