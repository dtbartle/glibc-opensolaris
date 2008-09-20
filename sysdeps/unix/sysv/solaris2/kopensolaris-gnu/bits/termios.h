/* termios type and macro definitions.  OpenSolaris version.
   Copyright (C) 1993, 1994, 1995, 1996, 1997, 1998, 1999, 2003, 2005, 2008
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

#ifndef _TERMIOS_H
# error "Never include <bits/termios.h> directly; use <termios.h> instead."
#endif

typedef unsigned char	cc_t;
typedef unsigned int	speed_t;
typedef unsigned int	tcflag_t;

#define NCCS 19
struct termios
  {
    tcflag_t c_iflag;		/* input mode flags */
    tcflag_t c_oflag;		/* output mode flags */
    tcflag_t c_cflag;		/* control mode flags */
    tcflag_t c_lflag;		/* line discipline mode flags */
    cc_t c_cc[NCCS];		/* control characters */
  };

/* c_cc characters */
#define VINTR 0
#define VQUIT 1
#define VERASE 2
#define VKILL 3
#define VEOF 4
#define VEOL 5
#define VEOL2 6
#define VMIN 4
#define VTIME 5
#define VSWTCH 7
#define VSWTC VSWTCH
#define VSTART 8
#define VSTOP 9
#define VSUSP 10
#define VDSUSP 11
#define VREPRINT 12
#define VDISCARD 13
#define VWERASE 14
#define VLNEXT 15

/* c_iflag bits */
#define IGNBRK	0000001
#define BRKINT	0000002
#define IGNPAR	0000004
#define PARMRK	0000010
#define INPCK	0000020
#define ISTRIP	0000040
#define INLCR	0000100
#define IGNCR	0000200
#define ICRNL	0000400
#define IUCLC	0001000
#define IXON	0002000
#define IXANY	0004000
#define IXOFF	0010000
#define IMAXBEL	0020000
#define DOSMODE	0100000

/* c_oflag bits */
#define OPOST	0000001
#define OLCUC	0000002
#define ONLCR	0000004
#define OCRNL	0000010
#define ONOCR	0000020
#define ONLRET	0000040
#define OFILL	0000100
#define OFDEL	0000200
#if defined __USE_MISC || defined __USE_XOPEN
# define NLDLY	0000400
# define   NL0	0000000
# define   NL1	0000400
# define CRDLY	0003000
# define   CR0	0000000
# define   CR1	0001000
# define   CR2	0002000
# define   CR3	0003000
# define TABDLY	0014000
# define   TAB0	0000000
# define   TAB1	0004000
# define   TAB2	0010000
# define   TAB3	0014000
# define BSDLY	0020000
# define   BS0	0000000
# define   BS1	0020000
# define FFDLY	0100000
# define   FF0	0000000
# define   FF1	0100000
#endif

#define VTDLY	0040000
#define   VT0	0000000
#define   VT1	0040000

#ifdef __USE_MISC
# define XTABS	0014000
#endif

#ifdef __USE_MISC
# define PAGEOUT	0200000
# define WRAP	0400000
#endif

/* c_cflag bit meaning */
#if defined(__USE_MISC)
# define CBAUD	0000017
#endif
#define  B0	0000000		/* hang up */
#define  B50	0000001
#define  B75	0000002
#define  B110	0000003
#define  B134	0000004
#define  B150	0000005
#define  B200	0000006
#define  B300	0000007
#define  B600	0000010
#define  B1200	0000011
#define  B1800	0000012
#define  B2400	0000013
#define  B4800	0000014
#define  B9600	0000015
#define  B19200	0000016
#define  B38400	0000017
#define  B57600	0000020
#define  B76800	0000021
#define  B115200	0000022
#define  B153600	0000023
#define  B230400	0000024
#define  B307200	0000025
#define  B460800	0000026
#define __MAX_BAUD	B460800
#define CSIZE	0000060
#define   CS5	0000000
#define   CS6	0000020
#define   CS7	0000040
#define   CS8	0000060
#define CSTOPB	0000100
#define CREAD	0000200
#define PARENB	0000400
#define PARODD	0001000
#define HUPCL	0002000
#define CLOCAL	0004000
#ifdef __USE_MISC
# define RCV1EN		0010000
# define XMT1EN		0020000
# define LOBLK		0040000
# define XCLUDE		0100000
# define CRTSXOFF	010000000000
# define CRTSCTS	020000000000
# define CRTSCTS	020000000000
# define CIBAUD		03600000
# define PAREXT		04000000
# define CBAUDEXT	010000000
# define CIBAUDEXT	020000000
# define CRTS_IFLOW	010000000000
# define CCTS_OFLOW	020000000000
#endif

/* c_lflag bits */
#define ISIG	0000001
#define ICANON	0000002
#if defined __USE_MISC || defined __USE_XOPEN
# define XCASE	0000004
#endif
#define ECHO	0000010
#define ECHOE	0000020
#define ECHOK	0000040
#define ECHONL	0000100
#define NOFLSH	0000200
#define TOSTOP	0000400
#ifdef __USE_MISC
# define ECHOCTL 0001000
# define ECHOPRT 0002000
# define ECHOKE	 0004000
# define FLUSHO	 0010000
# define PENDIN	 0040000
#endif
#define IEXTEN	0100000

/* tcflow() and TCXONC use these */
#define	TCOOFF		0
#define	TCOON		1
#define	TCIOFF		2
#define	TCION		3

/* tcflush() and TCFLSH use these */
#define	TCIFLUSH	0
#define	TCOFLUSH	1
#define	TCIOFLUSH	2

/* tcsetattr uses these */
#ifndef _TIOC
# define    _TIOC   ('T'<<8)
#endif
#define	TCSANOW		(_TIOC|14)
#define	TCSADRAIN	(_TIOC|15)
#define	TCSAFLUSH	(_TIOC|16)


#define _IOT_termios /* Hurd ioctl type field.  */ \
  _IOT (_IOTS (cflag_t), 4, _IOTS (cc_t), NCCS, _IOTS (speed_t), 2)

#define LDIOC		('D'<<8)
#define LDOPEN		(LDIOC|0)
#define LDCLOSE		(LDIOC|1)
#define LDCHG		(LDIOC|2)
#define LDGETT		(LDIOC|8)
#define LDSETT		(LDIOC|9)
#define LDSMAP		(LDIOC|110)
#define LDGMAP		(LDIOC|111)
#define LDNMAP		(LDIOC|112)
#define LDEMAP		(LDIOC|113)
#define LDDMAP		(LDIOC|114)

#define DIOC		('d'<<8)
#define DIOCGETP	(DIOC|8)
#define DIOCSETP	(DIOC|9)

#define FIORDCHK	(('f'<<8)|3)

#define CESC	'\\'
#define CNUL	0
#define CDEL	0377
