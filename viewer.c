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
#include <string.h>
#include "rterm.h"
#include "viewer.h"
#include "global.h"
#include "fileb.h"
#include "keyb.h"
/*====================================================================*/
/* FUNCTIONS - CODE                                                   */
/*====================================================================*/
#define TABSIZE 8
#define MAXCOL 512
int bColor = B_CYAN;
int fColor = F_BLACK;
int highIntensity = 0;

int readPage(FILE *fp, long pointer, int shiftH) {
    long lines = 0;
    int k = 0;
    int i = 1, j = 1;
    wint_t ch = 0;

    if (fp == NULL) return -1;
    rewind(fp);

    // Skip lines for vertical scroll
    while (lines < pointer && ch != WEOF) {
        ch = fgetwc(fp);
        if (ch == 10) lines++;
    }

    // Write taking into account vertical pointer(pointer) and horizontal shift (shiftH)
    int col = 0;       // absolute column in file
    int line_len = 0;  // how many chars we actually drew in this row

    while (ch != WEOF) {
        ch = fgetwc(fp);

        if (ch == 10) {   // newline
            // clear the rest of the line with spaces
            if (line_len < new_columns - 2) {
                for (k = line_len + 1; k < new_columns - 2; k++) {
                    if (j < new_rows - 1) write_ch(k, j, ' ', bColor, fColor);
                }
                if (j < new_rows - 1) printf("\n");
            }
            j++;
            i = 1;
            col = 0;
            line_len = 0;

        } else if (ch == 9) {   // TAB handling
            int next_col = (col / TABSIZE + 1) * TABSIZE;
            while (col < next_col) {
                if (col >= shiftH && i < new_columns - 2) {
                    if (j < new_rows - 1)
                        write_ch(i, j, ' ', bColor, fColor);
                    i++;
                    line_len++;
                }
                col++;
            }

        } else {   // normal character
            // skip until horizontal scroll offset
            if (col >= shiftH) {
                if (i < new_columns - 2) {
                    if (ch > 20 && (j < new_rows - 1)) {
                        write_ch(i, j, ch, bColor, fColor);
                    }
                    i++;
                    line_len++;
                }
            }
            col++;
        }

        // last line
        if (j == (new_rows - 1)) {
            ch = fgetwc(fp);
            if (ch == 9) {   // TAB on last line
                int next_col = (col / TABSIZE + 1) * TABSIZE;
                while (col < next_col && j == new_rows - 2) {
                    if (col >= shiftH && i < new_columns - 2) {
                        write_ch(i, j, ' ', bColor, fColor);
                        i++;
                    }
                    col++;
                }
            } else if (ch > 20 && j == new_rows - 2) {
                write_ch(i, j, ch, bColor, fColor);
            }
            break;
        }
    }
    return 0;
}

int viewFile(char fileName[MAXFILENAME]){
   FILE *fp=NULL;
   long lines=0;
   long size=0;
   long pointer=0;
   int shiftH = 0;
   int exitSignal = 0;
   char ch = 0;
   char fileInfo[1024];
   char fileProgress[1024];
   long vscrollLimit = 0;
   char chartrail[5];
   int viewrows=0;
   int viewcolumns=0;
   int progress=0;
   //Resize loop
   do {
     strcpy(fileInfo,"\0");
     strcpy(fileProgress,"\0");
     ch = 0;
     vscrollLimit = 0;
     exitSignal = 0;
     pointer = 0;
     shiftH = 0;
     printf("%c[2J\r", 0x1b);
     draw_window(0, 0, new_columns-1, new_rows-1, bColor,fColor, B_WHITE,1,1,0);
     printf("\n");
     gotoxy(0,0);
     if (openFile(&fp, fileName, "r")) {
       size = getfileSize(fileName);
       lines = countLinesFile(fileName);
       sprintf(fileInfo,"[%s] FileSize: %ld | Lines: %ld",fileName, size,lines+1);
      write_str(0,0,fileInfo,B_WHITE,FH_BLACK);
       readPage(fp,pointer,shiftH);
       vscrollLimit = lines - (new_rows-2);
       //navigation loop
       do {
         //file stats progress
         progress = (pointer*100/vscrollLimit);
         sprintf(fileInfo,"Progress [%d]%c  | Col [%d]  ",progress,'%',shiftH);
         write_str(1,new_rows,fileInfo,B_WHITE,FH_BLACK);

 	 //check for screen resize 
         get_terminal_dimensions(&viewrows,&viewcolumns);
         if (viewrows != new_rows || viewcolumns != new_columns)
	         break;

         //Process Special Arrow Keys
      	 if (kbhit(1)) {
		 	ch = readch();
	 }
	 else ch=0;

	if (ch == K_ESCAPE)	// escape key
		{
			strcpy(chartrail, "\0");
			read_keytrail(chartrail);

			if (chartrail[0] == K_ESCAPE && chartrail[1] == 0) {
				//escape
				exitSignal = 1;
				break;
			}
			if (strcmp(chartrail, K_UP_TRAIL) == 0) {
	            	  if (pointer>0) pointer--;
	                  readPage(fp,pointer,shiftH);
			}
       
			if (strcmp(chartrail, K_DOWN_TRAIL) == 0) {
                          if (pointer<vscrollLimit) pointer++;
	                  readPage(fp,pointer,shiftH);
 
			}
			if (strcmp(chartrail, K_RIGHT_TRAIL) == 0) {
		          if(shiftH<MAXCOL) shiftH++;
	                  readPage(fp,pointer,shiftH);
			}

			if (strcmp(chartrail, K_LEFT_TRAIL) == 0) {
		           if (shiftH>0) shiftH--;
	                   readPage(fp,pointer,shiftH);
	                }
			if (strcmp(chartrail, K_PAGEUP_TRAIL) == 0) {
                          if (pointer >= new_rows - 2)
                              pointer = pointer - (new_rows - 2);
                          else
                             pointer = 0;  // stop at the top	                  
		         readPage(fp,pointer,shiftH);
			}
       
			if (strcmp(chartrail, K_PAGEDOWN_TRAIL) == 0) {
                          if (pointer + (new_rows - 2) <= vscrollLimit)
                            pointer =  pointer + (new_rows - 2);
                          else
                            pointer = vscrollLimit;  // stop at the limit of our scroll
                         readPage(fp, pointer, shiftH);	      
			}

			if (strcmp(chartrail, K_HOME_TRAIL) == 0 || strcmp(chartrail, K_HOME_TRAIL) == 0 ) {
			     pointer =0;
                             readPage(fp, pointer, shiftH);	      
			}
			if (strcmp(chartrail, K_END_TRAIL) == 0 || strcmp(chartrail, K_END_TRAIL2) == 0 ) {
			     pointer = vscrollLimit;
                             readPage(fp, pointer, shiftH);	      
			}


			if (strcmp(chartrail, K_F2_TRAIL) == 0 || strcmp(chartrail, K_F2_TRAIL2) == 0 ) {
				if (bColor < B_WHITE) bColor = bColor+1;
				else bColor = 39;
				break;
			}

			if (strcmp(chartrail, K_F3_TRAIL) == 0 || strcmp(chartrail, K_F3_TRAIL2) == 0 ) {
				if (fColor < F_WHITE) fColor = fColor+1;
				else fColor = 29;
				break;
			}
			if (strcmp(chartrail, K_F4_TRAIL) == 0 || strcmp(chartrail, K_F4_TRAIL2) == 0 ) {
				if (highIntensity == 60) {
					bColor = bColor - highIntensity;
					fColor = fColor - highIntensity;
					highIntensity = 0;
				}
				else{
				        highIntensity = 60;
					bColor = bColor + highIntensity;
					fColor = fColor + highIntensity;
					
				}
				break;
			}

	         }	

       } while (exitSignal !=1);
     } 
   new_columns = viewcolumns;
   new_rows = viewrows;
   closeFile(fp);
   fp = NULL; 
  } while (exitSignal != 1);  
   
  resetAnsi(0); 
  return 0;
}

