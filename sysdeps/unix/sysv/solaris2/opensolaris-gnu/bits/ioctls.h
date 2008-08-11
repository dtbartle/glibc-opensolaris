/* Copyright (C) 2008 Free Software Foundation, Inc.
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

#ifndef _SYS_IOCTL_H
# error "Never use <bits/ioctls.h> directly; include <sys/ioctl.h> instead."
#endif

#define	IOCPARM_MASK	0xff
#define	IOC_VOID	0x20000000
#define	IOC_OUT		0x40000000
#define	IOC_IN		0x80000000
#define	IOC_INOUT	(IOC_IN|IOC_OUT)

#define _IOC(inout,group,num,len) \
	(inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define	_IO(g,n)		_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)		_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IORN(g,n,t)	_IOC(IOC_OUT,	(g), (n), (t))
#define	_IOW(g,n,t)		_IOC(IOC_IN,	(g), (n), sizeof(t))
#define	_IOWN(g,n,t)	_IOC(IOC_IN,	(g), (n), (t))
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))
#define	_IOWRN(g,n,t)	_IOC(IOC_INOUT,	(g), (n), (t))


#define	SIOCSHIWAT	_IOW('s',  0, int)
#define	SIOCGHIWAT	_IOR('s',  1, int)
#define	SIOCSLOWAT	_IOW('s',  2, int)
#define	SIOCGLOWAT	_IOR('s',  3, int)
#define	SIOCATMARK	_IOR('s',  7, int)
#define	SIOCSPGRP	_IOW('s',  8, int)
#define	SIOCGPGRP	_IOR('s',  9, int)

#define	SIOCGETNAME	_IOR('s',  52, struct sockaddr)
#define	SIOCGETPEER	_IOR('s',  53, struct sockaddr)
#define	IF_UNITSEL	_IOW('s',  54, int)
#define	SIOCXPROTO	_IO('s',   55)


#define	SIOCADDRT	_IOWN('r', 10, 48)
#define	SIOCDELRT	_IOWN('r', 11, 48)
#define	SIOCGETVIFCNT	_IOWR('r', 20, struct sioc_vif_req)
#define	SIOCGETSGCNT	_IOWR('r', 21, struct sioc_sg_req)
#define	SIOCGETLSGCNT	_IOWR('r', 21, struct sioc_lsg_req)


#define	SIOCSIFADDR		_IOW('i',  12, struct ifreq)
#define	SIOCGIFADDR		_IOWR('i', 13, struct ifreq)
#define	SIOCSIFDSTADDR		_IOW('i',  14, struct ifreq)
#define	SIOCGIFDSTADDR		_IOWR('i', 15, struct ifreq)
#define	SIOCSIFFLAGS	_IOW('i',  16, struct ifreq)
#define	SIOCGIFFLAGS	_IOWR('i', 17, struct ifreq)
#define	SIOCSIFMEM		_IOW('i',  18, struct ifreq)
#define	SIOCGIFMEM		_IOWR('i', 19, struct ifreq)
#define	O_SIOCGIFCONF	_IOWRN('i', 20, 8)
#define	SIOCSIFMTU		_IOW('i',  21, struct ifreq)
#define	SIOCGIFMTU		_IOWR('i', 22, struct ifreq)
#define	SIOCGIFBRDADDR		_IOWR('i', 23, struct ifreq)
#define	SIOCSIFBRDADDR		_IOW('i',  24, struct ifreq)
#define	SIOCGIFNETMASK		_IOWR('i', 25, struct ifreq)
#define	SIOCSIFNETMASK		_IOW('i',  26, struct ifreq)
#define	SIOCGIFMETRIC	_IOWR('i', 27, struct ifreq)
#define	SIOCSIFMETRIC	_IOW('i',  28, struct ifreq)

#define	SIOCSARP	_IOW('i',  30, struct arpreq)
#define	SIOCGARP	_IOWR('i', 31, struct arpreq)
#define	SIOCDARP	_IOW('i',  32, struct arpreq)
#define	SIOCUPPER	_IOW('i',  40, struct ifreq)
#define	SIOCLOWER	_IOW('i',  41, struct ifreq)
#define	SIOCSETSYNC		_IOW('i',  44, struct ifreq)
#define	SIOCGETSYNC		_IOWR('i', 45, struct ifreq)
#define	SIOCSSDSTATS	_IOWR('i', 46, struct ifreq)
#define	SIOCSSESTATS	_IOWR('i', 47, struct ifreq)
#define	SIOCSPROMISC	_IOW('i',  48, int)
#define	SIOCADDMULTI	_IOW('i',  49, struct ifreq)
#define	SIOCDELMULTI	_IOW('i',  50, struct ifreq)


#define	SIOCIFDETACH	_IOW('i',  56, struct ifreq)
#define	SIOCGENPSTATS	_IOWR('i', 57, struct ifreq)

#define	SIOCX25XMT		_IOWR('i', 59, struct ifreq)
#define	SIOCX25RCV		_IOWR('i', 60, struct ifreq)
#define	SIOCX25TBL		_IOWR('i', 61, struct ifreq)

#define	SIOCSLGETREQ	_IOWR('i', 71, struct ifreq)
#define	SIOCSLSTAT		_IOW('i',  72, struct ifreq)
#define	SIOCSIFNAME		_IOW('i',  73, struct ifreq)

#define	SIOCGENADDR		_IOWR('i', 85, struct ifreq)

#define	SIOCGIFNUM		_IOR('i',  87, int)
#define	SIOCGIFMUXID	_IOWR('i', 88, struct ifreq)
#define	SIOCSIFMUXID	_IOW('i',  89, struct ifreq)
#define	SIOCGIFINDEX	_IOWR('i', 90, struct ifreq)
#define	SIOCSIFINDEX	_IOW('i',  91, struct ifreq)
#define	SIOCGIFCONF		_IOWRN('i', 92, 8)

#define	SIOCLIFREMOVEIF		_IOW('i',  110, struct lifreq)
#define	SIOCLIFADDIF	_IOWR('i', 111, struct lifreq)
#define	SIOCSLIFADDR	_IOW('i',  112, struct lifreq)
#define	SIOCGLIFADDR	_IOWR('i', 113, struct lifreq)
#define	SIOCSLIFDSTADDR		_IOW('i',  114, struct lifreq)
#define	SIOCGLIFDSTADDR		_IOWR('i', 115, struct lifreq)
#define	SIOCSLIFFLAGS	_IOW('i',  116, struct lifreq)
#define	SIOCGLIFFLAGS	_IOWR('i', 117, struct lifreq)

#define	O_SIOCGLIFCONF		_IOWRN('i', 120, 16)
#define	SIOCSLIFMTU		_IOW('i',  121, struct lifreq)
#define	SIOCGLIFMTU		_IOWR('i', 122, struct lifreq)
#define	SIOCGLIFBRDADDR		_IOWR('i', 123, struct lifreq)
#define	SIOCSLIFBRDADDR		_IOW('i',  124, struct lifreq)
#define	SIOCGLIFNETMASK		_IOWR('i', 125, struct lifreq)
#define	SIOCSLIFNETMASK		_IOW('i',  126, struct lifreq)
#define	SIOCGLIFMETRIC		_IOWR('i', 127, struct lifreq)
#define	SIOCSLIFMETRIC		_IOW('i',  128, struct lifreq)
#define	SIOCSLIFNAME	_IOWR('i',  129, struct lifreq)
#define	SIOCGLIFNUM		_IOWR('i', 130, struct lifnum)
#define	SIOCGLIFMUXID	_IOWR('i', 131, struct lifreq)
#define	SIOCSLIFMUXID	_IOW('i',  132, struct lifreq)
#define	SIOCGLIFINDEX	_IOWR('i', 133, struct lifreq)
#define	SIOCSLIFINDEX	_IOW('i',  134, struct lifreq)
#define	SIOCSLIFTOKEN	_IOW('i',  135, struct lifreq)
#define	SIOCGLIFTOKEN	_IOWR('i', 136, struct lifreq)
#define	SIOCSLIFSUBNET		_IOW('i',  137, struct lifreq)
#define	SIOCGLIFSUBNET		_IOWR('i', 138, struct lifreq)
#define	SIOCSLIFLNKINFO		_IOW('i',  139, struct lifreq)
#define	SIOCGLIFLNKINFO		_IOWR('i', 140, struct lifreq)
#define	SIOCLIFDELND	_IOW('i',  141, struct lifreq)
#define	SIOCLIFGETND	_IOWR('i', 142, struct lifreq)
#define	SIOCLIFSETND	_IOW('i',  143, struct lifreq)
#define	SIOCTMYADDR		_IOWR('i', 144, struct sioc_addrreq)
#define	SIOCTONLINK		_IOWR('i', 145, struct sioc_addrreq)
#define	SIOCTMYSITE		_IOWR('i', 146, struct sioc_addrreq)
#define	SIOCGTUNPARAM	_IOR('i',  147, struct iftun_req)
#define	SIOCSTUNPARAM	_IOW('i',  148, struct iftun_req)
#define	SIOCFIPSECONFIG		_IOW('i',  149, 0)
#define	SIOCSIPSECONFIG		_IOW('i',  150, 0)
#define	SIOCDIPSECONFIG		_IOW('i',  151, 0)
#define	SIOCLIPSECONFIG		_IOW('i',  152, 0)
#define	SIOCLIFFAILOVER		_IOW('i',  153, struct lifreq)
#define	SIOCLIFFAILBACK		_IOW('i',  154, struct lifreq)
#define	SIOCSLIFGROUPNAME	_IOW('i',  155, struct lifreq)
#define	SIOCGLIFGROUPNAME	_IOWR('i',  156, struct lifreq)
#define	SIOCGLIFOINDEX		_IOWR('i', 157, struct lifreq)
#define	SIOCSLIFOINDEX		_IOWR('i', 161, struct lifreq)
#define	SIOCGIP6ADDRPOLICY	_IOWRN('i', 162, 0)
#define	SIOCSIP6ADDRPOLICY	_IOWN('i', 163, 0)
#define	SIOCGDSTINFO	_IOWRN('i', 164, 0)
#define	SIOCGLIFCONF	_IOWRN('i', 165, 16)
#define	SIOCSXARP	_IOW('i', 166, struct xarpreq)
#define	SIOCGXARP	_IOWR('i', 167, struct xarpreq)
#define	SIOCDXARP	_IOW('i', 168, struct xarpreq)
#define	_SIOCSOCKFALLBACK	_IOW('i', 169, 0)
#define	SIOCGLIFZONE	_IOWR('i', 170, struct lifreq)
#define	SIOCSLIFZONE	_IOW('i', 171, struct lifreq)
#define	SIOCSCTPSOPT	_IOWN('i', 172, 16)
#define	SIOCSCTPGOPT	_IOWRN('i', 173, 16)
#define	SIOCSCTPPEELOFF		_IOWR('i', 174, int)
#define	SIOCGLIFUSESRC		_IOWR('i', 175, struct lifreq)
#define	SIOCSLIFUSESRC		_IOW('i', 176, struct lifreq)
#define	SIOCGLIFSRCOF	_IOWRN('i', 177, 16)
#define	SIOCGMSFILTER	_IOWR('i', 178, 0)
#define	SIOCSMSFILTER	_IOW('i', 179, 0)
#define	SIOCGIPMSFILTER		_IOWR('i', 180, 0)
#define	SIOCSIPMSFILTER		_IOW('i', 181, 0)
#define	SIOCSIPMPFAILBACK	_IOW('i', 182, int)
#define	SIOCSENABLESDP		_IOWR('i', 183, int)


#define	FIOCLEX		_IO('f', 1)
#define	FIONCLEX	_IO('f', 2)

#define	_FIOISBUSY		_IO('f', 75)
#define	_FIODIRECTIO	_IO('f', 76)
#define	_FIOTUNE	_IO('f', 77)

#define	_FIOLOGENABLE	_IO('f', 87)
#define	_FIOLOGDISABLE		_IO('f', 88)
#define	_FIOSNAPSHOTCREATE		_IO('f', 89)
#define	_FIOSNAPSHOTDELETE		_IO('f', 90)
#define	_FIOGETSUPERBLOCK	_IO('f', 91)
#define	_FIOGETMAXPHYS		_IO('f', 92)
#define	_FIO_SET_LUFS_DEBUG		_IO('f', 93)
#define	_FIO_SET_LUFS_ERROR		_IO('f', 94)
#define	_FIO_GET_TOP_STATS		_IO('f', 95)
#define	_FIOSNAPSHOTCREATE_MULTI	_IO('f', 96)
#define	_FIO_SEEK_DATA		_IO('f', 97)
#define	_FIO_SEEK_HOLE		_IO('f', 98)
#define	_FIO_COMPRESSED		_IO('f', 99)

#define	FIONREAD	_IOR('f', 127, int)
#define	FIONBIO		_IOW('f', 126, int)
#define	FIOASYNC	_IOW('f', 125, int)
#define	FIOSETOWN	_IOW('f', 124, int)
#define	FIOGETOWN	_IOR('f', 123, int)


#ifndef IOCTYPE
#define	IOCTYPE	0xff00
#endif


#ifndef _TIOC
# define	_TIOC	('T'<<8)
# define	TIOC	_TIOC
#endif

#define	TCGETA	(_TIOC|1)
#define	TCSETA	(_TIOC|2)
#define	TCSETAW	(_TIOC|3)
#define	TCSETAF	(_TIOC|4)
#define	TCSBRK	(_TIOC|5)
#define	TCXONC	(_TIOC|6)
#define	TCFLSH	(_TIOC|7)
#define	TIOCKBON	(_TIOC|8)
#define	TIOCKBOF	(_TIOC|9)
#define	KBENABLED	(_TIOC|10)

#define	TCGETS		(_TIOC|13)
#define	TCSETS		(_TIOC|14)
#define	TCSETSW		(_TIOC|15)
#define	TCSETSF		(_TIOC|16)

#define	TCDSET	(_TIOC|32)
#define	RTS_TOG	(_TIOC|33)

#define	TIOCSWINSZ (_TIOC|103)
#define	TIOCGWINSZ (_TIOC|104)
#define	TIOCGSOFTCAR (_TIOC|105)
#define	TIOCSSOFTCAR (_TIOC|106)

#define	TIOCSETLD	(_TIOC|123)
#define	TIOCGETLD	(_TIOC|124)


#define	tIOC	('t'<<8)

#define	TIOCGETD	(tIOC|0)
#define	TIOCSETD	(tIOC|1)
#define	TIOCHPCL	(tIOC|2)
#define	TIOCGETP	(tIOC|8)
#define	TIOCSETP	(tIOC|9)
#define	TIOCSETN	(tIOC|10)
#define	TIOCEXCL	(tIOC|13)
#define	TIOCNXCL	(tIOC|14)
#define	TIOCFLUSH	(tIOC|16)
#define	TIOCSETC	(tIOC|17)
#define	TIOCGETC	(tIOC|18)

#define	TIOCGPGRP	(tIOC|20)
#define	TIOCSPGRP	(tIOC|21)
#define	TIOCGSID	(tIOC|22)
#define	TIOCSTI		(tIOC|23)

#define	TIOCMSET	(tIOC|26)
#define	TIOCMBIS	(tIOC|27)
#define	TIOCMBIC	(tIOC|28)
#define	TIOCMGET	(tIOC|29)
#define	TIOCREMOTE	(tIOC|30)
#define	TIOCSIGNAL	(tIOC|31)

#define	TIOCLBIS	(tIOC|127)
#define	TIOCLBIC	(tIOC|126)
#define	TIOCLSET	(tIOC|125)
#define	TIOCLGET	(tIOC|124)
#define	TIOCSBRK	(tIOC|123)
#define	TIOCCBRK	(tIOC|122)
#define	TIOCSDTR	(tIOC|121)
#define	TIOCCDTR	(tIOC|120)
#define	TIOCSLTC	(tIOC|117)
#define	TIOCGLTC	(tIOC|116)
#define	TIOCOUTQ	(tIOC|115)
#define	TIOCNOTTY	(tIOC|113)
#define	TIOCSCTTY	(tIOC|132)
#define	TIOCSTOP	(tIOC|111)
#define	TIOCSTART	(tIOC|110)
#define	TIOCSILOOP	(tIOC|109)


#define	TIOCM_LE	0001
#define	TIOCM_DTR	0002
#define	TIOCM_RTS	0004
#define	TIOCM_ST	0010
#define	TIOCM_SR	0020
#define	TIOCM_CTS	0040
#define	TIOCM_CAR	0100
#define	TIOCM_CD	TIOCM_CAR
#define	TIOCM_RNG	0200
#define	TIOCM_RI	TIOCM_RNG
#define	TIOCM_DSR	0400

#define TIOCPKT		_IOW('t', 112, int)
#define TIOCPKT_DATA		0x00
#define TIOCPKT_FLUSHREAD	0x01
#define TIOCPKT_FLUSHWRITE	0x02
#define TIOCPKT_STOP		0x04
#define TIOCPKT_START		0x08
#define TIOCPKT_NOSTOP		0x10
#define TIOCPKT_DOSTOP		0x20
#define TIOCPKT_IOCTL		0x40

#define TIOCUCNTL	_IOW('t', 102, int)
#define TIOCTCNTL	_IOW('t', 32, int)
#define TIOCISPACE	_IOR('t', 128, int)
#define TIOCISIZE	_IOR('t', 129, int)
#define	TIOCSSIZE	_IOW('t', 37, struct ttysize)
#define	TIOCGSIZE	_IOR('t', 38, struct ttysize)
