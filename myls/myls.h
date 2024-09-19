/* *******************************************************
   * @File                 : myls.h
   * @Author               : mohamed bahget hamam
   * @gmail                : mahamedhamam15@gmail.com
   *******************************************************
*/

#ifndef MY_LS_H
#define MY_LS_H

/* **************** macros section start *************** */

#define MAX_NAME_SIZE 10         // macro to the max size of the ls name(program_name).

/* **************** macros section end *************** */

extern int errno;   //ensure the program can access the global errno variable.

void do_ls(char *dir);
/* 
   * @brief              : function for listing the contents of a directory.
   *
   * @functionality      : opening te directory , reading dir. entries, filering hidden files, printing file names , closing the directory.
   * 
   * @param=>(dir)       : pointer to the path of the directory.   
*/

int check_for_dir(char *dir); 
/* 
   * @brief              : function check if the directory exists or no.
   *
   * @functionality      : return 1 if the directory exits and -1 if no and 0 if option.
   * 
   * @param=>(dir)       : pointer to the path of the directory.   
*/



#endif  





/* *******************************************************
   @User                 @Date              @time
   *******************************************************
   mohamed hamam         12sept2024         08:15 pm  
   mohamed hamam         19sept2024         07:40 pm        
*/