/* *******************************************************
   * @File                 : sort.c
   * @Author               : mohamed bahget hamam
   * @gmail                : mahamedhamam15@gmail.com
   *******************************************************
*/

/* **************** Include section start *************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "sort.h"

/* **************** Include section end *************** */


/* **************** defination section start *************** */

void bubble_sort(char *arr[], int n) 
{
   int i = 0 ;
   int j = 0 ;

   for ( i = 0; i < n - 1; i++) 
   {
      for ( j = 0; j < n - i - 1; j++)
      {
         if (strcmp(arr[j], arr[j + 1]) > 0) 
         {
            
            char *temp = arr[j];
            arr[j] = arr[j + 1];
            arr[j + 1] = temp;
               
         }

      }

   }
}

void sort_by_time (char *arr[] , int n , char *dir)
{
   struct stat stat_1 , stat_2 ;

   int i = 0 , j = 0 ;

   for ( i = 0 ; i < n - 1 ; i++ )
   {
      for ( j = 0 ; j < n - i - 1 ; j++)
      {
         char path_1[MAX_FILE_SIZE] , path_2[MAX_FILE_SIZE];
            
         snprintf(path_1 , sizeof(path_1) , "%s/%s" , dir , arr[j]);
         snprintf(path_2 , sizeof(path_2) , "%s/%s" , dir , arr[j + 1]);

         if (lstat(path_1, &stat_1) == -1 || lstat(path_2, &stat_2) == -1)
         {
            perror("lstat");
            exit(1);
         }

         if (stat_1.st_mtime < stat_2.st_mtime )
         {
            char *temp = arr[j] ; 
            arr[j] = arr[j + 1] ;
            arr[j + 1] = temp ;
         }
      }
   }

}

void sort_by_acs_time(char *arr[] , int n , char *dir)
{
   struct stat stat_1 , stat_2 ;

   int i = 0 , j = 0 ;

   for ( i = 0 ; i < n - 1 ; i++ )
   {
      for ( j = 0 ; j < n - i - 1 ; j++)
      {
         char path_1[MAX_FILE_SIZE] , path_2[MAX_FILE_SIZE];
            
         snprintf(path_1 , sizeof(path_1) , "%s/%s" , dir , arr[j]);
         snprintf(path_2 , sizeof(path_2) , "%s/%s" , dir , arr[j + 1]);

         if (lstat(path_1, &stat_1) == -1 || lstat(path_2, &stat_2) == -1)
         {
            perror("lstat");
            exit(1);
         }

         if (stat_1.st_atime < stat_2.st_atime)
         {
            char *temp = arr[j] ; 
            arr[j] = arr[j + 1] ;
            arr[j + 1] = temp ;
         }
      }
   }

}

void sort_by_last_mod_time(char *arr[] , int n , char *dir)
{
   struct stat stat_1 , stat_2 ;

   int i = 0 , j = 0 ;

   for ( i = 0 ; i < n - 1 ; i++ )
   {
      for ( j = 0 ; j < n - i - 1 ; j++)
      {
         char path_1[MAX_FILE_SIZE] , path_2[MAX_FILE_SIZE];
            
         snprintf(path_1 , sizeof(path_1) , "%s/%s" , dir , arr[j]);
         snprintf(path_2 , sizeof(path_2) , "%s/%s" , dir , arr[j + 1]);

         if (lstat(path_1, &stat_1) == -1 || lstat(path_2, &stat_2) == -1)
         {
            perror("lstat");
            exit(1);
         }

         if (stat_1.st_ctime < stat_2.st_ctime)
         {
            char *temp = arr[j] ; 
            arr[j] = arr[j + 1] ;
            arr[j + 1] = temp ;
         }
      }
   }
}



/* **************** defination section end *************** */


/* *******************************************************
   @User                 @Date              @time
   *******************************************************
   mohamed hamam         12sept2024         08:15 pm    
   mohamed hamam         19sept2024         07:40 pm   
*/