//File reader [fread]
//Coded by v3l0r3k
//Date: August 2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileb.h"
#include "global.h"
#include "rterm.h"
#include "listc.h"
#include "keyb.h"
#include "opfile.h"
#include "viewer.h"

int main() {
   int exitsignal = 0;
   int bytes = 0;
   //char ch = 0;
   get_terminal_dimensions (&new_rows,&new_columns);
   old_rows = new_rows;
   old_columns = new_columns;
   init_term();
   hidecursor();  
   strcpy(fileName, "\0");
   strcpy(fullPath, "\0");
   do{
   get_terminal_dimensions (&new_rows,&new_columns);
	 if (openFileDialog(fileName,fullPath) == 0){ 
	   if (scrollData.lastch == K_ENTER) {
		 if (openandcheckFile(fileName) == 1){
			yesnoWindow("File appears binary. Program|may crash. Open anyway?","Alert");
		 } else{
		   if (fileName[0] != '\0') viewFile(fileName);
		 }
	   }
	 }
	 if (scrollData.lastch == K_ESCAPE && scrollData.screenChanged == 0) exitsignal = 1;
   } while (exitsignal != 1);
   showcursor();   
   close_term();
   printf("%s\n", fileName);
   printf("%s\n", fullPath);
   printf("%d\n",scrollData.screenChanged);
   printf("%d\n",bytes);
   return 0;
}
