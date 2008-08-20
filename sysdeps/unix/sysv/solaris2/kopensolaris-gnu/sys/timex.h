/* Copyright (C) 1995, 1996, 1997, 1999, 2008 Free Software Foundation, Inc.
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

#ifndef	_SYS_TIMEX_H
#define	_SYS_TIMEX_H	1

#include <features.h>
#include <sys/time.h>
#include <sys/types.h>

struct ntptimeval
{
  struct timeval time;	/* current time (ro) */
  int32_t maxerror;	/* maximum error (us) (ro) */
  int32_t esterror;	/* estimated error (us) (ro) */
};

struct timex
{
  uint32_t modes;	/* mode selector */
  int32_t offset;	/* time offset (usec) */
  int32_t freq;	/* frequency offset (scaled ppm) */
  int32_t maxerror;	/* maximum error (usec) */
  int32_t esterror;	/* estimated error (usec) */
  int32_t status;		/* clock command/status */
  int32_t constant;	/* pll time constant */
  int32_t precision;	/* clock precision (usec) (read only) */
  int32_t tolerance;	/* clock frequency tolerance (ppm) (read only) */
  int32_t ppsfreq;	/* pps frequency (scaled ppm) (ro) */
  int32_t jitter;	/* pps jitter (us) (ro) */
  int32_t shift;		/* interval duration (s) (shift) (ro) */
  int32_t stabil;	/* pps stability (scaled ppm) (ro) */
  int32_t jitcnt;	/* jitter limit exceeded (ro) */
  int32_t calcnt;	/* calibration intervals (ro) */
  int32_t errcnt;	/* calibration errors (ro) */
  int32_t stbcnt;	/* stability limit exceeded (ro) */
};

/* Engineering parameters of the PLL.  */
#define SCALE_KG	(1<<6)
#define SCALE_KF	(1<<16)
#define SCALE_KH	(1<<2)
#define MAXTC		(1<<6)


/* PLL variables.  */
#define SCALE_PHASE		(1<<22)
#define SCALE_USEC		(1<<16)
#define SCALE_UPDATE	(SCALE_KG * MAXTC)
#define FINEUSEC		(1<<22)

/* Performance envelope of the PLL.  */
#define MAXPHASE	512000
#define MAXFREQ		(512 * SCALE_USEC)
#define MAXTIME		(200 << PPS_AVG)
#define MINSEC		16
#define MAXSEC		1200

/* Used if pulse-per-second (PPS) is present.  */
#define PPS_AVG		2
#define PPS_SHIFT	2
#define PPS_SHIFTMAX	8
#define PPS_VALID	120
#define MAXGLITCH	30

/* Mode codes (timex.mode) */
#define ADJ_OFFSET		0x0001	/* time offset */
#define ADJ_FREQUENCY		0x0002	/* frequency offset */
#define ADJ_MAXERROR		0x0004	/* maximum time error */
#define ADJ_ESTERROR		0x0008	/* estimated time error */
#define ADJ_STATUS		0x0010	/* clock status */
#define ADJ_TIMECONST		0x0020	/* pll time constant */
#define ADJ_TICK		0x4000	/* tick value */
#define ADJ_OFFSET_SINGLESHOT	0x8000	/* old-fashioned adjtime */

/* xntp 3.4 compatibility names */
#define MOD_OFFSET	ADJ_OFFSET
#define MOD_FREQUENCY	ADJ_FREQUENCY
#define MOD_MAXERROR	ADJ_MAXERROR
#define MOD_ESTERROR	ADJ_ESTERROR
#define MOD_STATUS	ADJ_STATUS
#define MOD_TIMECONST	ADJ_TIMECONST
#define MOD_CLKB	ADJ_TICK
#define MOD_CLKA	ADJ_OFFSET_SINGLESHOT /* 0x8000 in original */


/* Status codes (timex.status) */
#define STA_PLL		0x0001	/* enable PLL updates (rw) */
#define STA_PPSFREQ	0x0002	/* enable PPS freq discipline (rw) */
#define STA_PPSTIME	0x0004	/* enable PPS time discipline (rw) */
#define STA_FLL		0x0008	/* select frequency-lock mode (rw) */

#define STA_INS		0x0010	/* insert leap (rw) */
#define STA_DEL		0x0020	/* delete leap (rw) */
#define STA_UNSYNC	0x0040	/* clock unsynchronized (rw) */
#define STA_FREQHOLD	0x0080	/* hold frequency (rw) */

#define STA_PPSSIGNAL	0x0100	/* PPS signal present (ro) */
#define STA_PPSJITTER	0x0200	/* PPS signal jitter exceeded (ro) */
#define STA_PPSWANDER	0x0400	/* PPS signal wander exceeded (ro) */
#define STA_PPSERROR	0x0800	/* PPS signal calibration error (ro) */

#define STA_CLOCKERR	0x1000	/* clock hardware fault (ro) */

#define STA_RONLY (STA_PPSSIGNAL | STA_PPSJITTER | STA_PPSWANDER | \
    STA_PPSERROR | STA_CLOCKERR) /* read-only bits */

/* Clock states (time_state) */
#define TIME_OK		0	/* clock synchronized, no leap second */
#define TIME_INS	1	/* insert leap second */
#define TIME_DEL	2	/* delete leap second */
#define TIME_OOP	3	/* leap second in progress */
#define TIME_WAIT	4	/* leap second has occurred */
#define TIME_ERROR	5	/* clock not synchronized */
#define TIME_BAD	TIME_ERROR /* bw compat */

/* Maximum time constant of the PLL.  */
#define MAXTC		6

__BEGIN_DECLS

extern int __adjtimex (struct timex *__ntx) __THROW;
extern int adjtimex (struct timex *__ntx) __THROW;

extern int ntp_gettime (struct ntptimeval *__ntv) __THROW;
extern int ntp_adjtime (struct timex *__tntx) __THROW;

__END_DECLS

#endif /* sys/timex.h */
