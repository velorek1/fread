/*
======================================================================
Module to display a text file inside a window.

@author : Velorek
@version : 1.0

LAST MODIFIED : AUGUST 2025
======================================================================
*/

/*====================================================================*/
/* COMPILER DIRECTIVES AND INCLUDES                                   */
/*====================================================================*/

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "rterm.h"
#include "viewer.h"
#include "global.h"
#include "fileb.h"
/*====================================================================*/
/* FUNCTIONS - CODE                                                   */
/*====================================================================*/

int viewFile(char fileName[MAXFILENAME]){
   wint_t ch=0;
   int i=1 , j =1;
   FILE *fp=NULL;
   long lines=0;
   long size=0;
   char fileInfo[1024];
   printf("%c[2J\r", 0x1b);
   draw_window(0, 0, new_columns-1, new_rows-1, B_CYAN,F_BLACK, B_WHITE,1,1,0);
   printf("\n");
   gotoxy(0,0);
  if (openFile(&fp, fileName, "r")) {
       size = getfileSize(fileName);
       lines = countLinesFile(fileName);
       sprintf(fileInfo,"[%s] FileSize: %ld | Lines: %ld",fullPath, size,lines);
       write_str(0,0,fileInfo,B_WHITE,FH_BLACK);
	 if (fp != NULL) rewind(fp);
     while ((ch = fgetwc(fp)) != WEOF) {
  
	write_ch(i,j,ch,B_CYAN,F_BLACK);
       if (i<new_columns) i++;
         else {
		 if (j<new_rows-2) {
		 }
	 }
      if (ch == 10) {j++; i=1;};
    }
   do {
	  
       ch = readch();
    } while (ch!=27);
  }  
  closeFile(fp);
  fp = NULL;
 resetAnsi(0); 
  return 0;
}

