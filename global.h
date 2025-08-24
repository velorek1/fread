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

#include "listc.h"
extern LISTCHOICE *listBox1;
extern SCROLLDATA scrollData;
extern int new_rows, new_columns, old_rows, old_columns;	// Terminal dimensions
extern char fileName[MAXFILENAME]; 
extern char fullPath[MAXFILENAME]; 
extern FILE *filePointer;
int yesnoWindow(char *message, char *windowTitle);
int displayColorKey(void);


#endif
