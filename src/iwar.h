
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

void ncount( int ncount);
void NCURSES_Intro( void );
void npause( int );
void ninfo(const char *, int );  /* 1 = ERROR , 2 = WARN */

void NCURSES_Plot(long long dialnum, int row,  int col);

void nright(int, int);

void drawinfo(const char *,  const char *, const char *,  const char *,
              const char *,  const char *, const char *,  int,
              int, int,  int, int, int, int, int);

char *nsimpleform();

void NCURSES_Filename(char *str, size_t size);


void usage( void );
void closetty( int );
void rowcolcheck( void );
void sendmodem( const char *);
void dtrreinit( const char *, int );
void plushangup( int );
void loginfo( int, const char *,  const char *, const char *);
void exitscreen ( int, int, int, int, int, int, int);
int  getnum( int, int, int, const char *,  const char * );


