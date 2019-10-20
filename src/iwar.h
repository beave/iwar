/*
** Copyright (C) 2005-2019 - Champ Clark III - dabeave@gmail.com
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#ifndef HAVE_STRLCAT
size_t strlcat(char *, const char *, size_t );
#endif

#ifndef HAVE_STRLCPY
size_t strlcpy(char *, const char *, size_t );
#endif

/**************************************************/
/* Functions for ncurses (from iwar-ncurses.c)    */
/**************************************************/

void NCURSES_Mainscreen( void );
void NCURSES_Status( char *status );
void NCURSES_Timer( int timer );
void NCURSES_Count(int ncount);
void NCURSES_Intro( void );
void NCURSES_Pause( int type );
void NCURSES_Info(const char *msg, int type);  /* ERROR or WARN */
void NCURSES_Plot( uint64_t dialnum, int row,  int col );
void NCURSES_Right(int type, int value);
void NCURSES_Filename(char *str, size_t size);
void NCURSES_SimpleForm(char *str, size_t size);

void DrawInfo( const char *baudrate, const char *bits, const char *parity, const char *tty, \
               const char *numbersfile, const char *predial, const char *postdial, bool logtype, \
               int connect, int nocarrier, int busy, int voice, int tonesilence, bool dialtype, \
               int timeout );


void Usage( void );
void CloseTTY(int sig );
void RowColCheck( void );
void SendModem(const char *sendstring);
void DTRReInit(const char *modeminit, int volume);
void PlusHangup(int PlusHangupsleep);
void ExitScreen(int connect, int nocarrier, int voice, int busy, int tonesilence,  int mark, int skip);
void LogInfo(const char *response, const char *ident, const char *recordbuf );
int GetNumber(bool dialtype, bool tonedetect, const char *predial, const char *postdial);
uint64_t GetRandNumber (uint64_t begin, uint64_t end);
void Remove_Return(char *s);
int RSleep ( int redial, bool rtime );


