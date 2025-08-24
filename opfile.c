/*====================================================================*/
/* OPEN FILE MODULE
   +ListFiles with double linked list and selection menu in C.
   +Scroll function added.
   +Integrated with fread
   A window is drawn to the buffer and all of the scroll animations
   are drawn to the terminal on raw mode to have a better scrolling
   animation. Once the file is selected, the window is closed and the
   previous screen is painted to the terminal again.
   Last modified : August 2025 - Adapted from c-edit to fread
   Coded by Velorek.
   Target OS: Linux.                                                  */
/*====================================================================*/
#define _GNU_SOURCE
/*====================================================================*/
/* COMPILER DIRECTIVES AND INCLUDES */
/*====================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "fileb.h"
#include "rterm.h"
#include "listc.h"
#include "keyb.h"
#include "opfile.h"
#include "global.h"

/*====================================================================*/
/* GLOBAL VARIABLES */
/*====================================================================*/

int     window_x1 = 0, window_y1 = 0, window_x2 = 0, window_y2 = 0;
int ndirs=0, nfiles=0;
int bcol = BACKGROUNDCOLOR;
int fcol = FOREGROUNDCOLOR;
int titleB = TITLEBCOLOR;
int titleF = TITLEFCOLOR;

/*====================================================================*/
/* CODE */
/*====================================================================*/

int listFiles(LISTCHOICE ** listBox1, char *directory) {
  DIR    *d;
  struct dirent *dir;
  int     i;
  char    temp[MAX_ITEM_LENGTH];
  int     lenDir;       //length of directory
  ndirs=0;
  nfiles=0;
  if (*listBox1 != NULL) removeList(listBox1);
  *listBox1 = addatend(*listBox1, newitem("[..]",-1,-1,FH_WHITE,B_RED));    // ".."

  //Start at current directory
  d = opendir(directory);
  //Find directories and add them to list first
  if(d) {
    while((dir = readdir(d)) != NULL) {
      if(dir->d_type == DT_DIR) {

    lenDir = strlen(dir->d_name);

    //Check length of directory
    //Directories are displayed between brackets [directory]
    if(lenDir > MAX_ITEM_LENGTH - 2) {
      //Directory name is long. CROP
      memset(&temp, '\0',sizeof(temp)); //Clear memory for temporary line
      strcpy(temp,"\0");
      strcpy(temp, "[");
      for(i = 1; i < MAX_ITEM_LENGTH - 1; i++) {
        temp[i] = dir->d_name[i - 1];
      }
      temp[MAX_ITEM_LENGTH - 1] = ']';
    } else {
      //Directory's name is shorter than display
      //Add spaces to item string.
      memset(&temp, '\0',sizeof(temp)); //Clear memory for temporary line
      strcpy(temp,"\0");
      strcpy(temp, "[");
      for(i = 1; i < lenDir + 1; i++) {
        temp[i] = dir->d_name[i - 1];
      }
      temp[lenDir + 1] = ']';
    }
    //Add all directories except CURRENTDIR and CHANGEDIR
    if(strcmp(dir->d_name, ".") != 0
       && strcmp(dir->d_name, "..") != 0)
    { ndirs++;
      *listBox1 =
          addatend(*listBox1, newitem(temp, -1,-1,FH_WHITE,B_RED));}
      }
    }
  }
  closedir(d);

  //Find files and add them to list after directories
  d = opendir(directory);
  if(d) {
    while((dir = readdir(d)) != NULL) {
      if(dir->d_type == DT_REG) {
    //only list valid fiels
    if(strlen(dir->d_name) > MAX_ITEM_LENGTH) {
      for(i = 0; i < MAX_ITEM_LENGTH; i++) {
        temp[i] = dir->d_name[i];
      }
    } else {
      memset(&temp, '\0',sizeof(temp)); //Clear memory for temporary line
      strcpy(temp,"\0");
      strcpy(temp, dir->d_name);
    }
    nfiles++;
    if (openandcheckFile(dir->d_name) == 1) {
    *listBox1 =
        addatend(*listBox1, newitem(temp, -1,-1,-1,-1));
    }else{
     *listBox1 =
        addatend(*listBox1, newitem(temp, -1,-1,B_BLUE,FH_WHITE));
    }

    }
    }
    closedir(d);
  }
  
  return 0;
}

void addItems(LISTCHOICE **listBox1)
{
	int h=0;
//Load items into the list.  
        //if (listBox1 != NULL) removeList(listBox1);
	for (h = 0; h <10; h++) {
		//*ch = textarray[h];
		*listBox1 = addatend(*listBox1, newitem("Test",-1,-1,-1,-1));
	}
}

int openFileDialog(char fileName[MAXFILENAME], char fullPath[MAXFILENAME]){
char ch=0;
char path[MAXFILENAME];
char bit[MAXFILENAME];
char ndirstr[255];
size_t i=0;
int retvalue=0;
char currentPath[4] = "./\0";
    retvalue =0;
    setselectorLimit(new_columns-2);
    old_rows = new_rows;
    old_columns = new_columns; 
   do{
      draw_window(0, 0, new_columns, new_rows, bcol,fcol, B_WHITE,1,0,0);
      listFiles(&listBox1,currentPath);
      sprintf(ndirstr, "h: HELP | ESC: EXIT || [%d] Directories [%d] Files", ndirs, nfiles);
      getcwd(path, sizeof(path));	  
      write_str(1,new_rows,ndirstr,titleB,titleF);
      write_str(1,0,path,titleB,titleF);
      ch = listBox(listBox1, 2,2, &scrollData, bcol, fcol,B_BLACK, FH_WHITE, new_rows-2, VERTICAL,1,LOCKED);
      //if (_animation() == -1) {ch=K_ESCAPE; break;} 
      if (ch == 0x27) {break;} 
      if (ch == K_TAB) {break;} 
      if (ch =='h') {break;}
      if (ch =='a') {break;}
      if (ch ==K_SPACE) {break;}
      if (ch == K_ENTER){

        if (scrollData.item[0] == '[') {
	 //directory   
            memset(&path, '\0',sizeof(path)); //Clear memory for temporary line
            memset(&bit, '\0',sizeof(bit)); //Clear memory for temporary line
    	    strcpy(bit,"\0");
            strcpy(path,"\0");
            for (i=1; i<strlen(scrollData.item)-1; i++) bit[i-1] = scrollData.item[i];
	    getcwd(path, sizeof(path));
	    strcat(path, "/");
	    strcat(path, bit);
	    chdir(path);
	    ch=0;
     }
      else {

 	      break;
      }	 
    } 
   } while (ch!=K_ESCAPE);   
   // setselectorLimit(15);
   
     
    if (ch!=27){
    	    //we pass the values
            memset(fileName, '\0', strlen(fileName) + 1); // Clear memory for temporary line
            memset(fullPath, '\0', strlen(fullPath) + 1); // Clear memory for temporary line
           // memset(&fileName, '\0',sizeof(fileName)); //Clear memory for temporary line
    	    strcpy(bit,"\0");
            strcpy(path,"\0");
            strcpy(fileName, scrollData.item);
            getcwd(path, sizeof(path));
            strcpy(fullPath, path);
	    //reset scroll values
    }
    if (listBox1 != NULL) removeList(&listBox1);
   return retvalue;
}


