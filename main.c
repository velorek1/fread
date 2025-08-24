//TUI Text-File reader [fread]
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
   int ok =0;
   char csearch[MAXFILENAME];
   char ch = 0;
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
  //No arguments were given open file dialog loop
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
	 //Miscellaneous routines are found in global.c
	 if (scrollData.lastch == K_SPACE) {ch=displayColorKey(); if (ch == K_ESCAPE) {scrollData.lastch = 0;}}
	 if (scrollData.lastch == K_TAB) {
		    strcpy(csearch,"\0");
	            textbox(1, new_rows-1, 45,"File:", csearch, B_BLACK, F_WHITE, F_WHITE, 1);
		    if (strlen(csearch)>1 && file_exists(csearch)) {
			strcpy(fileName,csearch);
			viewFile(fileName);
		    }
	 }
	 if (scrollData.lastch == 'h') displayHelp();
	 if (scrollData.lastch == 'a') displayAbout();
  	 if (scrollData.lastch == K_ESCAPE && scrollData.screenChanged == 0) exitsignal = 1;
      } while (exitsignal != 1);
    }
   //credits
   showcursor();   
   close_term();
   return 0;
}
