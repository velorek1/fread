#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "global.h"
#include "rterm.h"

LISTCHOICE *listBox1 = NULL;
SCROLLDATA scrollData = {0};
int new_rows = 0, new_columns = 0, old_rows = 0, old_columns = 0;	// Terminal dimensions
char fileName[MAXFILENAME]={0}; 
char fullPath[MAXFILENAME]={0}; 
char help[HELPLINES][MAXLINE] = { HELP0,
	HELP1, HELP2, HELP3,
	HELP4, HELP5, HELP6,
	HELP7, HELP8, HELP9,
	HELP10, HELP11, HELP12,
	HELP13, HELP14, HELP15,
	HELP16, HELP17, HELP18,
	HELP19, HELP20
};
char aboutMSG[8][MAXLINE] =
    { ABOUT0, ABOUT1, ABOUT2, ABOUT3, ABOUT4, ABOUT5};

int yesnoWindow(char *message, char *windowTitle) {

  int     window_x1 = 0, window_y1 = 0, window_x2 = 0, window_y2 = 0;
  char ch = 0;
  int ok = 0;
  size_t i=0;
  int j = 0;
  int ix = 0;
  char tempChar=0;
  window_y1 = (new_rows / 2) - 4;
  window_y2 = (new_rows / 2) + 4;
  window_x1 = (new_columns / 2) - 16;
  window_x2 = (new_columns / 2) + 16;
  draw_window(window_x1, window_y1, window_x2, window_y2, B_WHITE, F_BLACK, F_BLACK,1,1,0);
  write_str((window_x2-window_x1) /2 + window_x1 - (strlen(windowTitle)/2) , window_y1, windowTitle, B_BLACK, F_WHITE);
 for(i = 0; i < strlen(message); i++) {
    tempChar = message[i];
    if (tempChar != '|'){
      write_ch(window_x1 + 1 + ix, window_y1 + 1 + j, tempChar, B_WHITE,F_BLACK);
    ix++;
    }else {
	    j++;
	    ix = 0;
    }
    }
  printf("\n");
  if (listBox1 != NULL) removeList(&listBox1);
  listBox1 = addatend(listBox1, newitem("[  YES ]",window_x1+3,window_y2,-1,-1));
  listBox1 = addatend(listBox1, newitem("[  NO  ]",window_x1+13,window_y2,-1,-1));
  listBox1 = addatend(listBox1, newitem("[ EXIT ]",window_x1+23,window_y2,-1,-1));

  setselectorLimit(8);
  ch = listBox(listBox1, window_x1+2,window_y2, &scrollData, B_WHITE, F_BLACK,B_RED, FH_WHITE, 3, HORIZONTAL,1,LOCKED);
  ok = scrollData.itemIndex;
  if (listBox1 != NULL) removeList(&listBox1);
  ch++;
  scrollData.lastch =0;
  return ok;
}

int displayColorKey(void)
{
	//Color Key
	char ch = 0;
        setselectorLimit(4);
	draw_window((new_columns / 2) - 11, (new_rows / 2) - 6,
	       (new_columns / 2) + 12, (new_rows) / 2 + 2, B_WHITE, F_BLACK,
	       B_BLACK, 1, 1, 1);
	write_str((new_columns / 2) - 10, (new_rows / 2) - 6,
		  "[+] COLOR KEY", B_BLACK, FH_WHITE);
	write_str((new_columns / 2) - 10, (new_rows / 2) - 1,
		  "      DIRECTORIES     ", B_RED, FH_WHITE);
	write_str((new_columns / 2) - 10, (new_rows / 2) - 2,
		  "      TEXT FILES      ", B_BLUE, FH_WHITE);
	write_str((new_columns / 2) - 10, (new_rows / 2) - 3,
		  "      BINARY FILES    ", B_BLACK, FH_WHITE);




	if (listBox1 != NULL)
		removeList(&listBox1);
	
	listBox1 = addatend(listBox1, newitem("[OK]",-1,-1,-1,-1));
	if (listBox1 != NULL)
		ch = listBox(listBox1, (new_columns / 2), (new_rows / 2) + 2,
			     &scrollData, B_WHITE, F_BLACK, B_RED, FH_WHITE, 1, VERTICAL,1,
			     LOCKED);
	if (listBox1 != NULL)
		removeList(&listBox1);
	scrollData.lastch =0;
	return ch;
}


int displayHelp(void)
{
	char ch = 0;
	int i =0;

	setselectorLimit((26 * 2) - 1);	//No. of chars per item display
	draw_window((new_columns / 2) - 26, (new_rows / 2) - 8,
		    (new_columns / 2) + 26, (new_rows) / 2 + 8, B_WHITE, F_BLACK,
		    B_BLACK, 1, 1, 1);
	write_str((new_columns / 2) - 1, (new_rows / 2) + 7, "[OK]",
		  B_RED, FH_WHITE);
	write_str((new_columns / 2) - 25, (new_rows / 2) - 8,
		  "[+] HELP", B_BLACK, FH_WHITE);

	if (listBox1 != NULL)
		removeList(&listBox1);
	for (i=0;i<HELPLINES;i++){
	    listBox1 = addatend(listBox1, newitem(help[i],-1,-1,-1,-1));
	}
	if (listBox1 != NULL)
		ch = listBox(listBox1, (new_columns / 2) - 24,
			     (new_rows / 2) - 6, &scrollData, B_WHITE, F_BLACK,
			     B_CYAN, FH_WHITE, 14, VERTICAL,1,LOCKED);
	if (listBox1 != NULL)
		removeList(&listBox1);
	scrollData.lastch =0;
	ch++;
	return ch;
}
void aboutmsg(){

	int i = 0;
	draw_window((new_columns / 2) - 28, (new_rows / 2) - 6,
	       (new_columns / 2) + 27, (new_rows) / 2 + 5, B_BLACK, F_WHITE,
	       B_WHITE, 1, 0, 1);
	for (i = 0; i < 4; i++) {
		write_str((new_columns / 2) - 15,
			  (new_rows / 2) - 5 + i, aboutMSG[i], B_BLACK,
			  F_WHITE);
	}
	write_str((new_columns / 2) - 25, (new_rows / 2) + 1,
		  aboutMSG[4], B_BLACK, F_CYAN);
	write_str((new_columns / 2) - 25, (new_rows / 2) + 2,
		  aboutMSG[5], B_BLACK, F_RED);
	write_str((new_columns / 2) - 1, (new_rows / 2) + 4, "[OK]",
		  B_WHITE, F_BLACK);
	printf("\n");

}
int displayAbout(void)
{
	char ch = 0;
	int x=0,y=0;
	int reset=0;
	int col =0, fcol=0;
        srand(time(NULL));  
	draw_window((new_columns / 2) - 28, (new_rows / 2) - 6,
	       (new_columns / 2) + 27, (new_rows) / 2 + 5, B_BLACK, F_WHITE,
	       B_WHITE, 1, 0, 1);
	
	do {
          if (kbhit(7))
		   ch = readch();

	 if (reset==200) {
		 aboutmsg(); 
	     reset = -1;}
	 else {
	       if (reset>-1) {
		  reset++; 
	    	   x = ((new_columns/2) -27) + rand() % 54;
	           y = ((new_rows/2) -5) + rand() % 9;
                    col = 0 +rand() % 3;
		    switch (col){
				case 0: fcol=F_WHITE;break;
				case 1: fcol=F_CYAN;break;
				case 2: fcol=F_RED;break;

		    }
		write_ch(x,y,L'·',B_BLACK,fcol);
		printf("\n");
              }
	 }
	if (ch == K_ENTER) break;
	} while (ch!=K_ESCAPE);
          
	scrollData.lastch =0;
	ch++;
	return ch;
}
