/*
 * sysdep1.c	system dependant routines.
 *
 *		m_dtrtoggle	- dropt dtr and raise it again
 *		m_break		- send BREAK signal
 *		m_getdcd	- get modem dcd status
 *		m_setdcd	- set modem dcd status
 *		m_savestate	- save modem state
 *		m_restorestate	- restore saved modem state
 *		m_nohang	- tell driver not to hang up at DTR drop
 *		m_hupcl		- set hangup on close on/off
 *		m_setparms	- set baudrate, parity and number of bits.
 *		m_readchk	- see if there is input waiting.
 *		m_wait		- wait for child to finish. Sysdep. too.
 *
 *		If it's possible, Posix termios are preferred.
 *
 *		This file was part of the minicom communications package,
 *		Copyright 1991-1995 Miquel van Smoorenburg.
 *
 *              Modified version became part of iWar in 2005.
 *
 *		This program is free software; you can redistribute it and/or
 *		modify it under the terms of the GNU General Public License
 *		as published by the Free Software Foundation; either version
 *		2 of the License, or (at your option) any later version.
 */
#include "sysdep.h"

/* Set hardware flow control. */
void m_sethwf(fd, on)
int fd, on;
{
#ifdef _DGUX_SOURCE
  struct termiox x;
#endif
#ifdef _POSIX
  struct termios tty;

  tcgetattr(fd, &tty);
  if (on)
	tty.c_cflag |= CRTSCTS;
  else
	tty.c_cflag &= ~CRTSCTS;
  tcsetattr(fd, TCSANOW, &tty);
#endif

#ifdef _DGUX_SOURCE
  if (ioctl(fd, TCGETX, &x) < 0) {
	fprintf(stderr, "can't get termiox attr.\n");
	return;
  }
  x.x_hflag = on ? RTSXOFF|CTSXON : 0;

  if (ioctl(fd, TCSETX, &x) < 0) {
	fprintf(stderr, "can't set termiox attr.\n");
	return;
  }
#endif
}

/* Set RTS line. Sometimes dropped. Linux specific? */
void m_setrts(fd)
int fd;
{
#if defined(TIOCM_RTS) && defined(TIOCMODG)
  int mcs;

  ioctl(fd, TIOCMODG, &mcs);
  mcs |= TIOCM_RTS;
  ioctl(fd, TIOCMODS, &mcs);
#endif
#ifdef _COHERENT
  ioctl(fd, TIOCSRTS, 0);
#endif
}

/*
 * Drop DTR line and raise it again.
 */
void m_dtrtoggle(fd,sec) 
int fd;
int sec;
{
#ifdef TIOCSDTR

  /* Use the ioctls meant for this type of thing. */
  ioctl(fd, TIOCCDTR, 0);
  if (sec>0) {
  sleep(sec);
  ioctl(fd, TIOCSDTR, 0);
  }

#else /* TIOCSDTR */
#  if defined (_POSIX) && !defined(_HPUX_SOURCE)

  /* Posix - set baudrate to 0 and back */
  struct termios tty, old;

  tcgetattr(fd, &tty);
  tcgetattr(fd, &old);
  cfsetospeed(&tty, B0);
  cfsetispeed(&tty, B0);
  tcsetattr(fd, TCSANOW, &tty);
  sleep(1);
  tcsetattr(fd, TCSANOW, &old);

#  else /* POSIX */
#    ifdef _V7

  /* Just drop speed to 0 and back to normal again */
  struct sgttyb sg, ng;
  
  ioctl(fd, TIOCGETP, &sg);
  ioctl(fd, TIOCGETP, &ng);
  
  ng.sg_ispeed = ng.sg_ospeed = 0;
  ioctl(fd, TIOCSETP, &ng);
  sleep(1);
  ioctl(fd, TIOCSETP, &sg);

#    endif /* _V7 */
#    ifdef _HPUX_SOURCE
  unsigned long mflag = 0L;

  ioctl(fd, MCSETAF, &mflag);
  ioctl(fd, MCGETA, &mflag);
  mflag = MRTS | MDTR;
  sleep(1);
  ioctl(fd, MCSETAF, &mflag);
#    endif /* _HPUX_SOURCE */
#  endif /* POSIX */
#endif /* TIOCSDTR */
}

/*
 * Send a break
 */
void m_break(fd)
int fd;
{ 
#ifdef _POSIX
  tcsendbreak(fd, 0);
#else
#  ifdef _V7
#    ifndef TIOCSBRK
  struct sgttyb sg, ng;

  ioctl(fd, TIOCGETP, &sg);
  ioctl(fd, TIOCGETP, &ng);
  ng.sg_ispeed = ng.sg_ospeed = B110;
  ng.sg_flags = BITS8 | RAW;
  ioctl(fd, TIOCSETP, &ng);
  write(fd, "\0\0\0\0\0\0\0\0\0\0", 10);
  ioctl(fd, TIOCSETP, &sg);
#    else
  ioctl(fd, TIOCSBRK, 0);
  sleep(1);
  ioctl(fd, TIOCCBRK, 0);
#    endif
#  endif
#endif
}

/*
 * Get the dcd status
 */
int m_getdcd(fd)
int fd;
{
#ifdef TIOCMODG
  int mcs;
   
  ioctl(fd, TIOCMODG, &mcs);
  return(mcs & TIOCM_CAR ? 1 : 0);
#else
  (void)fd;
  return(0); /* Impossible!! (eg. Coherent) */
#endif
}

/* Variables to save states in */
#ifdef _POSIX
static struct termios savetty;
 static int m_word;			
#else
#  if defined (_BSD43) || defined (_V7)
static struct sgttyb sg;
static struct tchars tch;
static int lsw;
static int m_word;
#  endif
#endif

/*
 * Save the state of a port
 */
void m_savestate(fd)
int fd;
{
#ifdef _POSIX
  tcgetattr(fd, &savetty);
#else
#  if defined(_BSD43) || defined(_V7)
  ioctl(fd, TIOCGETP, &sg);
  ioctl(fd, TIOCGETC, &tch);
#  endif
#  ifdef _BSD43
  ioctl(fd, TIOCLGET, &lsw);
#  endif
#endif
#ifdef TIOCMODG
  ioctl(fd, TIOCMODG, &m_word);
#endif
}

/*
 * Restore the state of a port
 */
void m_restorestate(fd)
int fd;
{
#ifdef _POSIX
  tcsetattr(fd, TCSANOW, &savetty);
#else
#  if defined(_BSD43) || defined(_V7)
  ioctl(fd, TIOCSETP, &sg);
  ioctl(fd, TIOCSETC, &tch);
#  endif
#  ifdef _BSD43  
  ioctl(fd, TIOCLSET, &lsw);
#  endif
#endif
#ifdef TIOCMODS
  ioctl(fd, TIOCMODS, &m_word);
#endif
}

/*
 * Set the line status so that it will not kill our process
 * if the line hangs up.
 */
/*ARGSUSED*/ 
void m_nohang(fd)
int fd;
{
#ifdef _POSIX
  struct termios sgg;
  
  tcgetattr(fd, &sgg);
  sgg.c_cflag |= CLOCAL;
  tcsetattr(fd, TCSANOW, &sgg);
#else
#  if defined (_BSD43) && defined(LNOHANG)
  int lsw;
  
  ioctl(fd, TIOCLGET, &lsw);
  lsw |= LNOHANG;
  ioctl(fd, TIOCLSET, &lsw);
#  endif
#  ifdef _COHERENT
  /* Doesn't know about this either, me thinks. */
#  endif
#endif
}

/*
 * Set hangup on close on/off.
 */
void m_hupcl(fd, on)
int fd;
int on;
{
  /* Eh, I don't know how to do this under BSD (yet..) */
#ifdef _POSIX
  struct termios sgg;
  
  tcgetattr(fd, &sgg);
  if (on)
  	sgg.c_cflag |= HUPCL;
  else
	sgg.c_cflag &= ~HUPCL;
  tcsetattr(fd, TCSANOW, &sgg);
#endif
}

/*
 * Flush the buffers
 */
void m_flush(fd)
int fd;
{
/* Should I Posixify this, or not? */
#ifdef TCFLSH
  ioctl(fd, TCFLSH, 2);
#endif
#ifdef TIOCFLUSH
#ifdef _COHERENT
  ioctl(fd, TIOCFLUSH, 0);
#else
  ioctl(fd, TIOCFLUSH, (void *)0);
#endif
#endif
}

/*
 * See if there is input waiting.
 * returns: 0=nothing, >0=something, -1=can't.
 */
int m_readchk(fd)
int fd;
{
#ifdef FIONREAD
  long i = -1;

  (void) ioctl(fd, FIONREAD, &i);
  return((int)i);
#else
#  if defined(F_GETFL) && defined(O_NDELAY)
  int i, old;
  char c;

  old = fcntl(fd, F_GETFL, 0);
  (void) fcntl(fd, F_SETFL, old | O_NDELAY);
  i = read(fd, &c, 1);
  (void) fcntl(fd, F_SETFL, old);

  return(i);
#  else
  return(-1);
#  endif
#endif
}

/*
 * Get maximum speed.
 * Returns maximum speed / 100. (192-1152)
 */
int m_getmaxspd()
{
#ifdef B115200
  return(1152);
#elif defined(B57600)
  return(576);
#elif defined(B38400)
  return(384);
#elif defined(EXTB)
  return(384);
#elif defined(B19200)
  return(192);
#elif defined(EXTA)
  return(192);
#else
  return(96);
#endif
}

/*
 * Set baudrate, parity and number of bits.
 */
void m_setparms(fd, baudr, par, bits, hwf, swf)
int fd;
char *baudr;
char *par;
char *bits;
int hwf;
int swf;
{
  int spd = -1;
  int newbaud;
  int bit = bits[0];

#ifdef _POSIX
  struct termios tty;

  tcgetattr(fd, &tty);
#else /* _POSIX */
  struct sgttyb tty;

  ioctl(fd, TIOCGETP, &tty);
#endif /* _POSIX */

  /* We generate mark and space parity ourself. */
  if (bit == '7' && (par[0] == 'M' || par[0] == 'S'))
	bit = '8';

  /* Check if 'baudr' is really a number */
  if ((newbaud = (atol(baudr) / 100)) == 0 && baudr[0] != '0') newbaud = -1;

  switch(newbaud) {
  	case 0:
#ifdef B0
			spd = B0;	break;
#else
			spd = 0;	break;
#endif
  	case 3:		spd = B300;	break;
  	case 6:		spd = B600;	break;
  	case 12:	spd = B1200;	break;
  	case 24:	spd = B2400;	break;
  	case 48:	spd = B4800;	break;
  	case 96:	spd = B9600;	break;
#ifdef B19200
  	case 192:	spd = B19200;	break;
#else /* B19200 */
#  ifdef EXTA
	case 192:	spd = EXTA;	break;
#   else /* EXTA */
	case 192:	spd = B9600;	break;
#   endif /* EXTA */
#endif	 /* B19200 */
#ifdef B38400
  	case 384:	spd = B38400;	break;
#else /* B38400 */
#  ifdef EXTB
	case 384:	spd = EXTB;	break;
#   else /* EXTB */
	case 384:	spd = B9600;	break;
#   endif /* EXTB */
#endif	 /* B38400 */
#ifdef B57600
	case 576:	spd = B57600;	break;
#endif
#ifdef B115200
	case 1152:	spd = B115200;	break;
#endif
  }
  
#if defined (_BSD43) && !defined(_POSIX)
  if (spd != -1) tty.sg_ispeed = tty.sg_ospeed = spd;
  /* Number of bits is ignored */

  tty.sg_flags = RAW | TANDEM;
  if (par[0] == 'E')
	tty.sg_flags |= EVENP;
  else if (par[0] == 'O')
	tty.sg_flags |= ODDP;
  else
  	tty.sg_flags |= PASS8 | ANYP;

  ioctl(fd, TIOCSETP, &tty);

#  ifdef TIOCSDTR
  /* FIXME: huh? - MvS */
  ioctl(fd, TIOCSDTR, 0);
#  endif
#endif /* _BSD43 && !_POSIX */

#if defined (_V7) && !defined(_POSIX)
  if (spd != -1) tty.sg_ispeed = tty.sg_ospeed = spd;
  tty.sg_flags = RAW;
  if (par[0] == 'E')
	tty.sg_flags |= EVENP;
  else if (par[0] == 'O')
	tty.sg_flags |= ODDP;

  ioctl(fd, TIOCSETP, &tty);
#endif /* _V7 && !POSIX */

#ifdef _POSIX

  if (spd != -1) {
	cfsetospeed(&tty, (speed_t)spd);
	cfsetispeed(&tty, (speed_t)spd);
  }

  switch (bit) {
  	case '5':
  		tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS5;
  		break;
  	case '6':
  		tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS6;
  		break;
  	case '7':
  		tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS7;
  		break;
  	case '8':
	default:
  		tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;
  		break;
  }		
  /* Set into raw, no echo mode */
  tty.c_iflag =  IGNBRK;
  tty.c_lflag = 0;
  tty.c_oflag = 0;
  tty.c_cflag |= CLOCAL | CREAD;
#ifdef _DCDFLOW
  tty.c_cflag &= ~CRTSCTS;
#endif
  tty.c_cc[VMIN] = 1;
  tty.c_cc[VTIME] = 5;

  if (swf)
	tty.c_iflag |= IXON | IXOFF;
  else
	tty.c_iflag &= ~(IXON|IXOFF|IXANY);

  tty.c_cflag &= ~(PARENB | PARODD);
  if (par[0] == 'E')
	tty.c_cflag |= PARENB;
  else if (par[0] == 'O')
	tty.c_cflag |= PARODD;

  tcsetattr(fd, TCSANOW, &tty);

  m_setrts(fd);
#endif /* _POSIX */

#ifndef _DCDFLOW
  m_sethwf(fd, hwf);
#endif
}

/*
 * Wait for child and return pid + status
 */
int m_wait(stt)
int *stt;
{
#if defined (_BSD43) && !defined(_POSIX)
  int pid;
  union wait st1;
  
  pid = wait((void *)&st1);
  *stt = (unsigned)st1.w_retcode + 256 * (unsigned)st1.w_termsig;
  return(pid);
#else
  int pid;
  int st1;
  
  pid = wait(&st1);
  *stt = (unsigned)WEXITSTATUS(st1) + 256 * (unsigned)WTERMSIG(st1);
  return(pid);
#endif
}
