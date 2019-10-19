

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
void NCURSES_Plot(long long dialnum, int row,  int col);
void NCURSES_Right(int type, int value);
void NCURSES_Filename(char *str, size_t size);
void NCURSES_SimpleForm(char *str, size_t size);

void DrawInfo( const char *baudrate, const char *bits, const char *parity, const char *tty, \
               const char *numbersfile, const char *predial, const char *postdial, int logtype, \
               int connect, int nocarrier, int busy, int voice, int tonesilence, int dialtype, \
               int timeout );


void Usage( void );
void CloseTTY(int sig );
void RowColCheck( void );
void SendModem(const char *sendstring);
void DTRReInit(const char *modeminit, int volume);
void PlusHangup(int PlusHangupsleep);
void ExitScreen(int connect, int nocarrier, int voice, int busy, int tonesilence,  int mark, int skip);
void LogInfo(const char *response, const char *ident, const char *recordbuf );
int GetNumber(int dialtype, int tonedetect, const char *predial, const char *postdial);


