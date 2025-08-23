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

int readPage(FILE *fp, long pointer, int shiftH) {
    long lines = 0;
    int k=0;
    int i = 1, j= 1;
    wint_t ch = 0;

    if (fp == NULL) return -1;
    rewind(fp);

    // Skip lines for vertical scroll
    while (lines < pointer && ch != WEOF) {
	ch = fgetwc(fp);
        if (ch == 10) lines++;
    }

    // Write taking into account vertical pointer(pointer) and horixontal shift (shiftH)
    int col = 0;       // absolute column in file
    int line_len = 0;  // how many chars we actually drew in this row

    while (ch  != WEOF) {
	    ch=fgetwc(fp);
        if (ch == 10) {
            // pad the rest of the line with spaces
            if (line_len < new_columns - 2) {
               for (k=line_len+1;k<new_columns-2;k++){
		       if (k<1) k = 1;
		       if( j<new_rows-1)write_ch(k,j,' ',B_RED,F_WHITE);
	       }
	       if (j<new_rows-1)printf("\n");
            }
            j++;
	    i = 1;
            col = 0;
            line_len = 0;

        } else {
            // skip until horizontal scroll offset
            if (col >= shiftH) {
                if (i < new_columns) {
                    if (ch!=10 && ch!=0 && (j<new_rows-1)) write_ch(i, j, ch, B_CYAN, F_BLACK);
                    i++;
                    line_len++;
                }
            }
            col++;
        }
        //last line
        if (j == (new_rows - 1)){
	     ch=fgetwc(fp);
             if (ch!=10 && ch!=0 && j == new_rows-2) write_ch(i, j, ch, B_CYAN, F_BLACK);
	    break;
	}
    }
/*
    // if the file ended before screen was full, clear last line
    if (line_len < new_columns - 2) {
         for (k=line_len+1;k<new_columns-2;k++){
		       if (k<1) k = 1;
		       write_ch(k,j,' ',B_RED,F_WHITE);
	       }
	       printf("\n");

    }
*/
    return 0;
}

int viewFile(char fileName[MAXFILENAME]){
   FILE *fp=NULL;
   long lines=0;
   long size=0;
   long pointer=0;
   int shiftH = 0;
   char ch = 0;
   char fileInfo[1024];
   long vscrollLimit = 0;
   printf("%c[2J\r", 0x1b);
   draw_window(0, 0, new_columns-1, new_rows-1, B_CYAN,F_BLACK, B_WHITE,1,1,0);
   printf("\n");
   gotoxy(0,0);
  if (openFile(&fp, fileName, "r")) {
       size = getfileSize(fileName);
       lines = countLinesFile(fileName);
       sprintf(fileInfo,"[%s] FileSize: %ld | Lines: %ld",fullPath, size,lines);
       write_str(0,0,fileInfo,B_WHITE,FH_BLACK);
       readPage(fp,pointer,shiftH);
       vscrollLimit = lines - (new_rows-2);
   do {
	  
       ch = readch();
       if (ch == 's') {
             if (pointer<vscrollLimit) pointer++;
	     readPage(fp,pointer,shiftH);
       }
       if (ch == 'w') {
             if (pointer>0) pointer--;
	     readPage(fp,pointer,shiftH);
       }
        if (ch =='d'){
	  if(shiftH<512) shiftH++;
	     readPage(fp,pointer,shiftH);

	}
        if (ch =='a'){
	  if (shiftH>0) shiftH--;
	     readPage(fp,pointer,shiftH);
	}

    } while (ch!=27);
  }  
  closeFile(fp);
  fp = NULL;
 resetAnsi(0); 
  return 0;
}

