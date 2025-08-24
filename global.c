#include <string.h>
#include "global.h"
#include "rterm.h"

LISTCHOICE *listBox1 = NULL;
SCROLLDATA scrollData = {0};
int new_rows = 0, new_columns = 0, old_rows = 0, old_columns = 0;	// Terminal dimensions
char fileName[MAXFILENAME]={0}; 
char fullPath[MAXFILENAME]={0}; 


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
  return ok;
}

int displayColorKey(void)
{
	//Color Key
	char ch = 0;
        setselectorLimit(4);
	draw_window((new_columns / 2) - 11, (new_rows / 2) - 6,
	       (new_columns / 2) + 12, (new_rows) / 2 + 2, B_WHITE, F_BLACK,
	       B_BLACK, 1, 1, 0);
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
	return ch;
}

