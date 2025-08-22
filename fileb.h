/*
========================================================================
- HEADER - 
Module to handle basic file operations
@author : Velorek
@version : 1.0  
Last modified: 14/04/2019 Rename headers                                                              
========================================================================
*/

#ifndef _FILEB_H_
#define _FILEB_H_

/*====================================================================*/
/* COMPILER DIRECTIVES AND INCLUDES                                   */
/*====================================================================*/

#include <stdio.h>

/*====================================================================*/
/* CONSTANTS                                                          */
/*====================================================================*/
#define END_LINE_CHAR 0x10


/*====================================================================*/
/* FUNCTION PROTOTYPES                                                */
/*====================================================================*/

int     openFile(FILE ** filePtr, char fileName[], char *mode);
int     closeFile(FILE * filePtr);
long    getfileSize(char * fileName);
long    countLinesFile(char *fileName);
int     openandcheckFile(char *fileName);
int     file_exists(char *fileName);

#endif
