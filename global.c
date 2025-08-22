#include "global.h"
#include "rterm.h"

LISTCHOICE *listBox1 = NULL;
SCROLLDATA scrollData = {0};
int new_rows = 0, new_columns = 0, old_rows = 0, old_columns = 0;	// Terminal dimensions
char fileName[MAXFILENAME]={0}; 
char fullPath[MAXFILENAME]={0}; 
FILE *filePointer=NULL;

