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

int main(int argc, char *argv[]){

   int exitsignal = 0;
   int bytes = 0;
   int ok =0;
   //char ch = 0;
   get_terminal_dimensions (&new_rows,&new_columns);
   old_rows = new_rows;
   old_columns = new_columns;
   init_term();
   hidecursor();  
   strcpy(fileName, "\0");
   strcpy(fullPath, "\0");
   //check arguments
   get_terminal_dimensions (&new_rows,&new_columns);
   
   if(file_exists(argv[1]) == 1 && argc>0) {   
      viewFile(argv[1]);
   }   else{
  //No arguments were given open file dialog
    do{
     get_terminal_dimensions (&new_rows,&new_columns);
	 if (openFileDialog(fileName,fullPath) == 0){ 
	   if (scrollData.lastch == K_ENTER) {
		 if (openandcheckFile(fileName) == 1){
			ok=yesnoWindow("File appears binary. Program|may crash. Open anyway?","Alert");
			if (ok==2) exitsignal=1;
			if (ok ==0) viewFile(fileName);
		 } else{
		   if (fileName[0] != '\0') viewFile(fileName);
		 }
	   }
	 }
	 //All of these can be found in opfile.c
	 if (scrollData.lastch == K_SPACE) displayColorKey();
	 //if (scrollData.lastch == 'x') displayHelp();
	 //if (scrollData.lastch == 'x') displayAbout();
  	 if (scrollData.lastch == K_ESCAPE && scrollData.screenChanged == 0) exitsignal = 1;
      } while (exitsignal != 1);
    }
   //credits
   showcursor();   
   close_term();
   printf("%s\n", fileName);
   printf("%s\n", fullPath);
   printf("%d\n",scrollData.screenChanged);
   printf("%d\n",bytes);
   return 0;
}
