/* *******************************************************
   * @File                 : sort.h
   * @Author               : mohamed bahget hamam
   * @gmail                : mahamedhamam15@gmail.com
   *******************************************************
*/

#ifndef SORT_H
#define SORT_H

/* **************** macros section start *************** */

#define MAX_FILE_SIZE 1024       // macro to the max size of the files that the directory contains.

/* **************** macros section end *************** */

void bubble_sort(char *arr[], int n);
/* 
   * @brief              : function to sort the file_names (array that contains the names of files in the directory).
   *
   * @functionality      : sort the files alphabetically.
   * 
   * @param=>(arr)       : pointer to the array of files.   
   * 
   * @param=>(n)         : size of the array.alphabetically.
*/

void sort_by_time (char *arr[] , int n , char *dir );
/* 
   * @brief              : function to sort the file_names (array that contains the names of files in the directory).
   *
   * @functionality      : sort the files by the modification time.
   * 
   * @param=>(arr)       : pointer to the array of files.   
   * 
   * @param=>(n)         : size of the array.alphabetically.
*/

void sort_by_acs_time(char *arr[] , int n , char *dir);
/* 
   * @brief              : function to sort the file_names (array that contains the names of files in the directory).
   *
   * @functionality      : sort the files by the access time.
   * 
   * @param=>(arr)       : pointer to the array of files.   
   * 
   * @param=>(n)         : size of the array.alphabetically.
*/

void sort_by_last_mod_time(char *arr[] , int n , char *dir);
/* 
   * @brief              : function to sort the file_names (array that contains the names of files in the directory).
   *
   * @functionality      : sort the files by the last modification time.
   * 
   * @param=>(arr)       : pointer to the array of files.   
   * 
   * @param=>(n)         : size of the array.alphabetically.
*/

void inode_index (char *arr[] , int n , char *dir );
/* 
   * @brief              : function to give you the inode index of the file.
   *
   * @functionality      : print the inonde number.
   * 
   * @param=>(arr)       : pointer to the array of files.   
   * 
   * @param=>(n)         : size of the array.alphabetically.
*/

#endif

/* *******************************************************
   @User                 @Date              @time
   *******************************************************
   mohamed hamam         12sept2024         08:15 pm  
   mohamed hamam         19sept2024         07:40 pm      
*/