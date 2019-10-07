/*
 * sysdep.h	
 *		This file was part of the minicom communications package,
 *		Copyright 1991-1995 Miquel van Smoorenburg.
 *
 *              Modified version became part of iWar 2005.
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 *
 */
 
#include <sys/types.h>
/* Include standard Posix header files. */
#if defined (_POSIX) || defined(_BSD43)
#  include <stdlib.h>
#  include <unistd.h>
#endif
#ifndef _COH3
#  include <sys/wait.h>
#endif
/* Now see if we need to use sgtty, termio or termios. */
#ifdef _SCO
#  define _IBCS2 /* So we get struct winsize :-) */
#endif
#if defined (_SYSV)
#  if !defined(_POSIX) || defined(_NO_TERMIOS)
#    include <sys/termio.h>
#  else
#    include <sys/termios.h>
#  endif
#else
#  if defined(_POSIX) && !defined(_NO_TERMIOS)
#    include <termios.h>
#  else
#    define _V7
#    include <sgtty.h>
#  endif
#endif
/* Some system-specific include files for modem control. */
#ifdef _HPUX_SOURCE
#  include <sys/modem.h>
#endif
#if defined(_BSD43) || defined (_SYSV)
#  ifndef SUN
#    include <sys/ioctl.h>
#  endif
#endif
#ifdef _COHERENT
#  include <sgtty.h>
#endif
#ifdef _DGUX_SOURCE
#  include <sys/termiox.h>
#endif

/* And more "standard" include files. */
#include <stdio.h>
#include <setjmp.h>

/* Be sure we know WEXITSTATUS and WTERMSIG */
#if !defined(_BSD43)
#  ifndef WEXITSTATUS
#    define WEXITSTATUS(s) (((s) >> 8) & 0377)
#  endif
#  ifndef WTERMSIG
#    define WTERMSIG(s) ((s) & 0177)
#  endif
#endif

/* Some ancient SysV systems don't define these */
#ifndef VMIN
#  define VMIN 4
#endif
#ifndef VTIME
#  define VTIME 5
#endif
#ifndef IUCLC
#  define IUCLC 0
#endif
#ifndef IXANY
#  define IXANY 0
#endif

/* Different names for the same beast. */
#ifndef TIOCMODG			/* BSD 4.3 */
#  ifdef TIOCMGET
#    define TIOCMODG TIOCMGET		/* Posix */
#  else
#    ifdef MCGETA
#      define TIOCMODG MCGETA		/* HP/UX */
#    endif
#  endif
#endif

#ifndef TIOCMODS
#  ifdef TIOCMSET
#    define TIOCMODS TIOCMSET
#  else
#    ifdef MCSETA
#      define TIOCMODS MCSETA
#    endif
#  endif
#endif

#ifndef TIOCM_CAR			/* BSD + Posix */
#  ifdef MDCD
#    define TIOCM_CAR MDCD		/* HP/UX */
#  endif
#endif

/* Define some thing that might not be there */
#ifndef TANDEM
#  define TANDEM 0
#endif
#ifndef BITS8
#  define BITS8 0
#endif
#ifndef PASS8
#  ifdef LLITOUT
#  define PASS8 LLITOUT
#  else
#  define PASS8 0
#  endif
#endif
#ifndef CRTSCTS
#  define CRTSCTS 0
#endif

/* If this is SysV without Posix, emulate Posix. */
#if defined(_SYSV)
#if !defined(_POSIX) || defined(_NO_TERMIOS)
#  define termios termio
#  ifndef TCSANOW
#    define TCSANOW 0
#  endif
#  define tcgetattr(fd, tty)        ioctl(fd, TCGETA, tty)
#  define tcsetattr(fd, flags, tty) ioctl(fd, TCSETA, tty)
#  define tcsendbreak(fd, len)      ioctl(fd, TCSBRK, 0)
#  define speed_t int
#  define cfsetispeed(xtty, xspd) \
		((xtty)->c_cflag = ((xtty)->c_cflag & ~CBAUD) | (xspd))
#  define cfsetospeed(tty, spd)
#endif
#endif

/* Redefine cfset{i,o}speed for Linux > 1.1.68 && libc < 4.5.21 */
#if defined (__linux__) && defined(CBAUDEX)
#  undef cfsetispeed
#  undef cfsetospeed
#  define cfsetispeed(xtty, xspd) \
		((xtty)->c_cflag = ((xtty)->c_cflag & ~CBAUD) | (xspd))
#  define cfsetospeed(tty, spd)
#endif
