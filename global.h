/*
 * Global variables are intented to be placed here
 * Last modified: August 2025
 * @author: velorek
 *
 */
#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#define MAXFILENAME 255
#define MAXLINE 255
#define HELPLINES 21
#include "listc.h"

#define HELP0 "fread                                              \0"
#define HELP1 "=======                                            \0"
#define HELP2 "[fread] is a fast terminal TUI text file reader    \0"
#define HELP3 "for GNU/Linux terminals. It has an open-file       \0"
#define HELP4 "dialog module that auto-detects whether a file is  \0"
#define HELP5 "binary or a text-file.                             \0"
#define HELP6 "The viewer module supports UTF8-Unicode encoding.  \0"
#define HELP7 "___________________________________________________\0"
#define HELP8 "[h] -> Display help dialog.                        \0"
#define HELP9 "[a] -> Display about dialog.                       \0"
#define HELP10 "[SPACE]-> Color key of the open file dialog.      \0"
#define HELP11 "[TAB]-> Set file name.                            \0"
#define HELP12 "Usage:                                            \0"
#define HELP13 "[1] ./fread                                       \0"
#define HELP14 "[2] ./fread FILENAME                              \0"
#define HELP15 "F2/F3/F4 Change back- and fore-ground colors.      \0"
#define HELP16 "___________________________________________________\0"
#define HELP17 "This program was coded in C & Vim in August 2025.  \0"
#define HELP18 "Some of the techniques used can be found in my     \0"
#define HELP19 "personal blog : oldstuff286.blogspot.com           \0"
#define HELP20 "Peace!  - by v3l0r3k | repo: github.com/velorek1 | \0"
#define ABOUT0 "  _|                        | \0"
#define ABOUT1 " |     __|  _ \\   _` |   _` | \0"
#define ABOUT2 " __|  |     __/  (   |  (   |  \0"
#define ABOUT3 " _|   _|   \\___| \\__,_| \\__,_| \0"
#define ABOUT4 "            Coded by v3l0r3k - v0.1 2025\0"
#define ABOUT5 "              oldstuff286.blogspot.com\0"

extern LISTCHOICE *listBox1;
extern SCROLLDATA scrollData;
extern int new_rows, new_columns, old_rows, old_columns;	// Terminal dimensions
extern char fileName[MAXFILENAME]; 
extern char fullPath[MAXFILENAME]; 
extern FILE *filePointer;
int yesnoWindow(char *message, char *windowTitle);
int displayColorKey(void);
int displayHelp(void);
void aboutmsg();
int displayAbout(void);


#endif
