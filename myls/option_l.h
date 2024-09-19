/* *******************************************************
   * @File                 : option_l.h
   * @Author               : mohamed bahget hamam
   * @gmail                : mahamedhamam15@gmail.com
   *******************************************************
*/

#ifndef OPTION_L_H
#define OPTION_L_H

#include <sys/stat.h>


/* **************** Macros section start *************** */

#define MAX_FILES     1024
#define MAX_FILE_SIZE 1024

#define COLOR_RESET   "\x1b[0m"     // Reset to default color
#define COLOR_DIR     "\x1b[1;34m"  // Blue for directories
#define COLOR_EXEC    "\x1b[1;32m"  // Green for executables
#define COLOR_LINK    "\x1b[1;36m"  // Cyan for symlinks
#define COLOR_REG     "\x1b[0m"     // Default color for regular files

/* **************** macros section end *************** */

extern void bubble_sort(char *arr[], int n);

extern void sort_by_time (char *arr[] , int n , char *dir );

extern void sort_by_acs_time(char *arr[] , int n , char *dir);

extern void sort_by_last_mod_time(char *arr[] , int n , char *dir);


char *get_permission(struct stat file_stat);
/*  
   * @brief                     : function to give you the permissions of the file or the directory.
   *
   * @functionality             : return the permissions.
   * 
   * @param=>(file_state)       : obj. of the struct stat.   
*/

void do_ls_option_l(char *dir_name);
/*  
   * @brief                     : function to do the long format of ls.
   *
   * @functionality             : lists the contents of a directory in long format.
   * 
   * @param=>(dir)              : pointer to the path of the directory. 
   * 
*/


#endif

/* *******************************************************
   @User                 @Date              @time
   *******************************************************
   mohamed hamam         15sept2024         11:40 pm 
   mohamed hamam         19sept2024         07:40 pm         
*/