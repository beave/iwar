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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "version.h"
#include <curses.h>
#include <string.h>
#include <form.h>
#include <unistd.h>
#include <stdlib.h>
#include "iserial.h"

#include "iwar-defs.h"
#include "iwar.h"

void NCURSES_Mainscreen( void )
{
    int b;
    int c;
    int maxrow;
    int maxcol;

    getmaxyx(stdscr,maxrow,maxcol); /* Current screen attributes */

    if (maxrow < 24 || maxcol < 80)
        {
            endwin();
            fprintf(stderr, "This program requires a screen size of 80x24\n");
            exit(1);
        }

    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_RED,   COLOR_BLUE);

    init_pair(3, COLOR_WHITE, COLOR_RED);     /* Error messages */
    init_pair(4, COLOR_BLACK, COLOR_YELLOW);  /* Warn message   */
    init_pair(5, COLOR_BLACK, COLOR_WHITE);   /* Intro message  */
    init_pair(6, COLOR_RED,   COLOR_WHITE);   /* Intro border   */

    init_pair(10, COLOR_WHITE, COLOR_BLACK);  /* NO CARRIER */
    init_pair(11, COLOR_GREEN, COLOR_BLACK);  /* CONNECT    */
    init_pair(12, COLOR_YELLOW, COLOR_BLACK); /* BUSY       */
    init_pair(13, COLOR_BLUE,  COLOR_BLACK);  /* VOICE      */

    init_pair(14, COLOR_MAGENTA,  COLOR_BLACK);  /* Already scanned */
    init_pair(15, COLOR_CYAN, COLOR_BLACK);      /* Blacklist number */
    init_pair(16, COLOR_RED, COLOR_BLACK);       /* Skipped number */

    attron(COLOR_PAIR(1));
    move(0,0);
    addch(ACS_ULCORNER);

    for (b = 0; b < maxcol-2; b++)
        {
            addch(ACS_HLINE);
        }
    addch(ACS_URCORNER);

    /* Probably a better way to do this .... */

    for (c=1; c < 9;  c++)
        {
            move(c,0);
            addch(ACS_VLINE);
            for (b = 0; b < maxcol-2; b++)
                {
                    addch(' ');
                }
            addch(ACS_VLINE);
        }

    attron(COLOR_PAIR(10));

    move(maxrow-8,0);
    addch(ACS_ULCORNER);
    for (b = 0; b < maxcol-2; b++)
        {
            addch(ACS_HLINE);
        }
    addch(ACS_URCORNER);

    move(maxrow-8, maxcol-20);
    printw("[Terminal Window]");
    for (c=maxrow-7; c < maxrow;  c++)
        {
            move(c,0);
            addch(ACS_VLINE);
            move(c,maxcol-1);
            addch(ACS_VLINE);
        }

    move(maxrow-1,0);
    addch(ACS_LLCORNER);
    for (b = 0; b < maxcol-2; b++)
        {
            addch(ACS_HLINE);
        }
    addch(ACS_LRCORNER);

    attron(COLOR_PAIR(1));

    move(1,0);
    addch(ACS_VLINE);
    printw(" Port Info       :");
    move(2,0);
    addch(ACS_VLINE);
    printw(" Start/End Scan  :");
    move(3,0);
    addch(ACS_VLINE);
    printw(" Pre/Post Dial   :");
    move(4,0);
    addch(ACS_VLINE);
    printw(" Log File        :");
    move(5,0);
    addch(ACS_VLINE);
    printw(" Status          :");
    move(6,0);
    addch(ACS_VLINE);
    printw(" Idle            :");

    move(8,0);
    addch(ACS_LLCORNER);
    for (b = 0; b < maxcol-2; b++)
        {
            addch(ACS_HLINE);
        }
    addch(ACS_LRCORNER);

    attron(COLOR_PAIR(1));
    move(1, maxcol-23);
    printw("CONNECT      :");
    move(2, maxcol-23);
    printw("NO CARRIER   :");
    move(3, maxcol-23);
    printw("BUSY         :");
    move(4, maxcol-23);
    printw("VOICE        :");
    move(5, maxcol-23);
    printw("TONE/SILENCE :");
    move(6, maxcol-23);
    printw("TIMEOUT      :");
    move(7,maxcol-23);
    printw("Numbers Left : ");


    refresh();   /* Draw! BANG! BANG! */
}

/* "Status:" part of the screen */

void NCURSES_Status( char *status )
{
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    attron(COLOR_PAIR(1));
    move(5,20);
    printw("                                 ");
    move(5,20);
    printw("%s", status);
    attroff(COLOR_PAIR(1));
    refresh();
}

/* Shows serial timer in seconds */

void NCURSES_Timer(int timer)
{
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    attron(COLOR_PAIR(1));
    move(6,20);
    printw("         ");
    move(6,20);
    printw("%d", timer);
    refresh();
}

/* Plot number on the screen.  Color is preset before getting here */

void NCURSES_Plot(long long dialnum, int row,  int col)
{
    move(row,col);
    printw("%lld", dialnum);
    refresh();
}

/* Some basic statistics */

void NCURSES_Right(int type, int value)
{
    int maxcol = 0;
    int maxrow = 0;
    int rrow = 0; 

    getmaxyx(stdscr,maxrow, maxcol);

    if (type==1) rrow=1;    /* CONNECT */
    if (type==2) rrow=2;    /* NO CARRIER */
    if (type==3) rrow=3;    /* BUSY */
    if (type==4) rrow=4;    /* VOICE */
    if (type==5) rrow=5;    /* TONE or silence detected */
    if (type==6) rrow=6;	/* TIMEOUT */

    attron(COLOR_PAIR(1) | A_NORMAL );
    move(rrow, maxcol-8);
    printw("%d", value);
    attroff(COLOR_PAIR(1) | A_NORMAL );
    refresh();
}

/* Number of numbers left to dial */

void NCURSES_Count(int ncount)
{
    int maxrow;
    int maxcol;
    getmaxyx(stdscr,maxrow,maxcol);
    attron(COLOR_PAIR(1));
    move(7, maxcol-8);
    printw("%d ", ncount);
    refresh();
}

/* Draws information box in the center of the screen.  Yellow for warning,
   red for errors (determined by mtype) */

void NCURSES_Info(const char *msg, int mtype)
{

    WINDOW *info;

    int i;
    int b;
    int maxrow;
    int maxcol;
    getmaxyx(stdscr,maxrow,maxcol);

    info = newwin(7,50, (maxrow - 7) / 2, (maxcol - 50) / 2);

    if (mtype == 1)
        {
            wattrset(info, COLOR_PAIR(3));
        }
    if (mtype == 2)
        {
            wattrset(info, COLOR_PAIR(4));
        }

    box(info, ACS_VLINE, ACS_HLINE);

    /* Fill in box */

    for (i=1; i<6; i++)
        {
            for (b=1; b<49; b++)
                {
                    mvwaddch(info,i,b, ' ');
                }
        }

    mvwprintw(info, 3, (50-strlen(msg)) / 2, "%s",  msg);
    wrefresh(info);
    sleep(1);
    delwin(info);
    touchwin(stdscr);
    refresh();
}

/* Screen for when the user pauses iWar */

void NCURSES_Pause(int type )
{
    WINDOW *info;

    int i;
    int b;
    int maxrow;
    int maxcol;
    getmaxyx(stdscr,maxrow,maxcol);

    info = newwin(7,50, (maxrow - 7) / 2, (maxcol - 50) / 2);

    wattrset(info, COLOR_PAIR(4));
    box(info, ACS_VLINE, ACS_HLINE);

    for (i=1; i<6; i++)
        {
            for (b=1; b<49; b++)
                {
                    mvwaddch(info,i,b, ' ');
                }
        }

    if ( type == 0 ) mvwprintw(info, 3, 9, "Paused - Hit any key to continue.");
    if ( type == 1 ) mvwprintw(info, 3, 9, "Paused and Marked: Any Key Resumes");

    wrefresh(info);

    while (getch() == -1)
        {
            sleep(1);
        }

    delwin(info);
    touchwin(stdscr);
    refresh();
}

void NCURSES_Filename(char *str, size_t size)
{
    FIELD *field[2];
    FORM  *form;
    WINDOW *form_win;

    char buf[255] = { 0 };

    int key, row, col, maxrow, maxcol;
    int i, b;

    char tmp[255] = { 0 };

    getmaxyx(stdscr, maxrow, maxcol);
    field[0] = new_field(1,53,0,0,0,0);
    field[1] = NULL;

    set_field_fore(field[0], COLOR_PAIR(10));
    set_field_back(field[0], COLOR_PAIR(10));

    form = new_form(field);
    scale_form(form, &row, &col);

    form_win = newwin( 4,  58, (maxrow - 7)/2, (maxcol - 57)/2);

    keypad(form_win, TRUE);

    wattron(form_win, COLOR_PAIR(6));
    for (i=1; i<8; i++)
        {
            for (b=1; b<57; b++)
                {
                    mvwaddch(form_win,i,b, ' ');
                }
        }

    set_form_win(form, form_win);
    set_form_sub(form, derwin(form_win, row, col, 2, 2));
    box(form_win, ACS_VLINE, ACS_HLINE);
    mvwprintw(form_win, 1, 2, "Enter Filename To Save State To: [Nothing Aborts]", row, col);
    post_form(form);
    wrefresh(form_win);

    while((key = wgetch(form_win)) != 0x0a )
        {
            switch(key)
                {
                case KEY_BACKSPACE:
                    form_driver(form, REQ_DEL_PREV);
                    form_driver(form, REQ_DEL_CHAR);
                    break;

                /* KEY_BACKSPACE never seems to work for me.
                These serve as a "backup" */

                case 0x08:
                    form_driver(form, REQ_DEL_PREV);
                    form_driver(form, REQ_DEL_CHAR);
                    break;
                case 0x7f:
                    form_driver(form, REQ_DEL_PREV);
                    form_driver(form, REQ_DEL_CHAR);
                    break;
                default:
                    form_driver(form, key);
                    snprintf(tmp, sizeof(tmp), "%c", key);
                    strlcat(buf, tmp, sizeof(buf));
                }
        }

    form_driver(form, REQ_VALIDATION);
    unpost_form(form);
    free_form(form);
    free_field(field[0]);
    delwin(form_win);
    touchwin(stdscr);
    refresh();

    snprintf(str, size, "%s", buf);

}


/* Get user input about a number.  This creates a dialog box for the user
   to enter data */

void NCURSES_SimpleForm(char *str, size_t size)
{

    FIELD *field[2];
    FORM  *form;
    WINDOW *form_win;

    int key, row, col, maxrow, maxcol;
    int i, b;
    char buf[255] = { 0 };
    char tmp[255] = { 0 };
    char *bufpoint;

    getmaxyx(stdscr, maxrow, maxcol);

    field[0] = new_field(4,53,0,0,0,0);
    field[1] = NULL;

    set_field_fore(field[0], COLOR_PAIR(10));
    set_field_back(field[0], COLOR_PAIR(10));

    form = new_form(field);
    scale_form(form, &row, &col);

    form_win = newwin( 8,  58, (maxrow - 7)/2, (maxcol - 57)/2);
    keypad(form_win, TRUE);

    wattron(form_win, COLOR_PAIR(6));
    for (i=1; i<8; i++)
        {
            for (b=1; b<57; b++)
                {
                    mvwaddch(form_win,i,b, ' ');
                }
        }

    set_form_win(form, form_win);
    set_form_sub(form, derwin(form_win, row, col, 2, 2));
    box(form_win, ACS_VLINE, ACS_HLINE);
    mvwprintw(form_win, 1, 2, "Enter Comment For This Number:", row, col);
    post_form(form);
    wrefresh(form_win);

    while((key = wgetch(form_win)) != 0x0a )
        {
            switch(key)
                {
                case KEY_BACKSPACE:
                    form_driver(form, REQ_DEL_PREV);
                    form_driver(form, REQ_DEL_CHAR);
                    break;

                case 0x08:
                    form_driver(form, REQ_DEL_PREV);
                    form_driver(form, REQ_DEL_CHAR);
                    break;
                case 0x7f:
                    form_driver(form, REQ_DEL_PREV);
                    form_driver(form, REQ_DEL_CHAR);
                    break;
                default:
                    form_driver(form, key);
                    snprintf(tmp, sizeof(tmp), "%c", key);
                    strlcat(buf, tmp, sizeof(buf));

                }
        }

    form_driver(form, REQ_VALIDATION);
    unpost_form(form);
    free_form(form);
    free_field(field[0]);
    delwin(form_win);
    touchwin(stdscr);
    refresh();

    snprintf(str, size, "%s", buf);

}

/* Hello.. My name is Da Beave.  I wrote this program,  and I'd like to
   welcome you to it.   That's what this part does :) */

void NCURSES_Intro()
{
    WINDOW *info;

    int i;
    int b;
    int maxrow;
    int maxcol;
    char msg[50] = { 0 };

    getmaxyx(stdscr,maxrow,maxcol);
    info = newwin(15,50, (maxrow - 7) / 2, (maxcol - 50) / 2);
    wattrset(info, COLOR_PAIR(6));
    box(info, ACS_VLINE, ACS_HLINE);

    wattrset(info, COLOR_PAIR(5));

    for (i=1; i<14; i++)
        {
            for (b=1; b<49; b++)
                {
                    mvwaddch(info,i,b, ' ');
                }
        }

    strncpy(msg, "Intelligent War Dialer  [iWar]", sizeof(msg));
    mvwprintw(info, 1, (50-strlen(msg)) / 2, "%s", msg);
    strncpy(msg, "https://github.com/beave/iwar", sizeof(msg));
    mvwprintw(info, 2, (50-strlen(msg)) / 2, "%s", msg);
    snprintf(msg, sizeof(msg), "Version: %s", VERSION);
    mvwprintw(info, 3, (50-strlen(msg)) / 2, "%s", msg);
    strncpy(msg, "\"Now with 101% more VoIP!\"", sizeof(msg));
    mvwprintw(info, 4, (50-strlen(msg)) / 2, "%s", msg);
    wattrset(info, COLOR_PAIR(6));
    strncpy(msg, "Written By Da Beave", sizeof(msg));
    mvwprintw(info, 6, (50-strlen(msg)) / 2, "%s", msg);
    wattrset(info, COLOR_PAIR(5));
    strncpy(msg, "Released XXX. XXth 2019", sizeof(msg));
    mvwprintw(info, 8, (50-strlen(msg)) / 2, "%s", msg);
    strncpy(msg, "Contact Information:", sizeof(msg));
    mvwprintw(info, 10, (50-strlen(msg)) / 2, "%s", msg);
    strncpy(msg, "Email: dabeave@gmail.com", sizeof(msg));
    mvwprintw(info, 11, (50-strlen(msg)) / 2, "%s", msg);
    strncpy(msg, "Twitter: @dabeave", sizeof(msg));
    mvwprintw(info, 12, (50-strlen(msg)) / 2, "%s", msg);

    wrefresh(info);
    sleep(3);
    delwin(info);
    touchwin(stdscr);
    refresh();
}
