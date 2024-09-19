/* *******************************************************
   * @File                 : option_l.c
   * @Author               : mohamed bahget hamam
   * @gmail                : mahamedhamam15@gmail.com
   *******************************************************
*/


/* **************** Include section start *************** */

#include <unistd.h>    // provide access to POSIX API.
#include <dirent.h>    // for DIR and struct dirent.
#include <stdlib.h>    // for exit().
#include <errno.h>     // defines errno.
#include <stdio.h>     // for I/O func. like printf.
#include <string.h>    // for strcpy().
#include <sys/types.h> // for data types used in system calls.
#include <pwd.h>       // for user information (getpwuid).
#include <grp.h>       // for group information (getgrgid).
#include <time.h>      // for time formatting.
#include "option_l.h"

/* **************** Include section End *************** */





/* **************** declaration section start *************** */

extern int show_hidden_files ;
extern int show_by_mod_time  ;
extern int show_by_acs_time  ;
extern int show_by_last_mod  ;
extern int show_inode        ;
extern int show_disable_sort ;   
extern int show_directory    ;
extern int show_color        ;        

/* **************** declaration section end *************** */


/* **************** Definition section start *************** */

char *get_permission(struct stat file_stat)
{
    static char permissions[11];

    permissions[0] = (S_ISDIR(file_stat.st_mode)) ? 'd' : '-' ;  // check the dirctory;

    // owner permissions

    permissions[1] = (file_stat.st_mode & S_IRUSR) ? 'r' : '-' ; // does it have the read permission ?

    permissions[2] = (file_stat.st_mode & S_IWUSR) ? 'w' : '-' ; // does it have the write permission ?

    if (file_stat.st_mode & S_ISUID) // for check the user execute permissons and the setuid.
    {
        permissions[3] = (file_stat.st_mode & S_IXUSR ) ? 's' : 'S' ; 
    }else
    {
        permissions[3] = (file_stat.st_mode & S_IXUSR) ? 'x' : '-' ;
    }

    // group permissions 

    permissions[4] = (file_stat.st_mode & S_IRGRP) ? 'r' : '-' ; // does it have the  read group permission ?

    permissions[5] = (file_stat.st_mode & S_IWGRP) ? 'w' : '-' ; // does it have the write group permission ?

    if (file_stat.st_mode & S_ISGID) // for check the group execute permissons and the setgid.
    {
        permissions[6] = (file_stat.st_mode & S_IXGRP) ? 's' : 'S' ;
    }else
    {
        permissions[6] = (file_stat.st_mode & S_IXGRP) ? 'x' : '-' ;
    }

    // others permissions

    permissions[7] = (file_stat.st_mode & S_IROTH) ? 'r' : '-' ; // does others have the  read  permission ?

    permissions[8] = (file_stat.st_mode & S_IWOTH) ? 'w' : '-' ; // does others have the  write group permission ?

    if (file_stat.st_mode & S_ISVTX) // check for the sticky bit
    {
        permissions[9] = (file_stat.st_mode & S_IXOTH) ? 't' : 'T';
    }else
    {
        permissions[9] = (file_stat.st_mode & S_IXOTH) ? 'x' : '-' ;
    }

    // NULL terminate the string.
    permissions[10] = '\0';

    return permissions;

}



void do_ls_option_l(char *dir_name)
{
    DIR *dir;                              // holds the directory pointer.
    struct dirent *entry;                  // holds each file enty.
    struct stat file_state;                // holds the metadata about each file.
    char path[MAX_FILE_SIZE];              // buffer is used to store the full file path for each entry.
    struct dirent *file_list[MAX_FILES];   // Array to store directory entries
    int file_count = 0;
    long total_blocks = 0;

    char *file_names[MAX_FILE_SIZE];   // array to store the name of the files.
    int file_counter = 0 ;             // counter to store the number of files.

    if (show_directory)
    {
        if (lstat(dir_name, &file_state) < 0)
        {
            perror("lstat");
            return;
        }

    
        if (show_inode)
        {
            printf("%ld ", file_state.st_ino);
        }

        printf("%s ", get_permission(file_state));
        printf("%ld ", file_state.st_nlink);

        struct passwd *pw = getpwuid(file_state.st_uid);
        struct group *gr = getgrgid(file_state.st_gid);

        printf("%s %s ", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");
        printf("%ld ", file_state.st_size);

        char time_buf[80];
        struct tm *timeinfo = localtime(&file_state.st_mtime);
        strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", timeinfo);
        printf("%s ", time_buf);

        if (show_color)
        {
            printf(COLOR_DIR "%s\n" COLOR_RESET, dir_name);
        }
        else
        {
            printf("%s\n", dir_name);
        }

        return;  // Don't process the contents of the directory further
    }


    if ((dir = opendir(dir_name)) == NULL)
    {
        return;
    }
    /* 
    * (open dir) => opens the directory specified by (dir)
    *
    * if if fails (return NULL), an error message is printed with (perror)
    *   
    */

    while ((entry = readdir(dir)) != NULL)
    {
        if(entry->d_name[0] == '.' && !show_hidden_files && !show_disable_sort) // filter the hidden files
        {
            continue;
        }

        file_names[file_counter] = strdup(entry->d_name);
        if (file_names[file_counter] == NULL)
        {
            fprintf(stderr , "Memory allocation failed for file name\n");
            exit(1);
        }
        file_counter++;

        if (file_counter >= MAX_FILE_SIZE )
        {
            fprintf(stderr,"Too much files in the directoy !!\n");
            exit(1);
        }

        snprintf(path, sizeof(path), "%s/%s", dir_name, entry->d_name);
        /*
        *(readdir) => reads each entry. 
        *
        * the full path is crated by concatenating the directory name (dir) and the file name(entry->d_name)
        */

        if (lstat(path, &file_state) < 0)
        {
            perror("lstat");
            continue;
        }
        /*
        *(lstat) => retrieves the file status for each file
        * 
        * if it fails , it prints an error and continues the next file.
        */

        struct dirent *entry_copy = malloc(sizeof(struct dirent));
        if (entry_copy == NULL)
        {
            perror("malloc");
            closedir(dir);

            return;
        }
        memcpy(entry_copy, entry, sizeof(struct dirent));

        file_list[file_count] = entry_copy;
        file_count++;
        total_blocks += file_state.st_blocks;

    }


    closedir(dir);
    
    if (!show_disable_sort)
    {
        if (show_by_acs_time)
        {   
            if (show_by_mod_time )
            {
                sort_by_acs_time(file_names, file_counter, dir_name);
            }
            else
            {   
                bubble_sort(file_names, file_counter);
            }
        }else if (show_by_last_mod)
        {
            if (show_by_mod_time )
            {
                sort_by_last_mod_time(file_names, file_counter, dir_name);
            }
            else
            {   
                bubble_sort(file_names, file_counter);
            }
        }
        else if (show_by_mod_time)
        {
            sort_by_time(file_names, file_counter, dir_name);
        }
        else
        {
            bubble_sort(file_names, file_counter);
        }
    }

    

    printf("total %ld\n", total_blocks / 2);  // Divide by 2 because blocks are in 512-byte units and ls reports in 1K units



    for (int i = 0; i < file_counter; i++)
    {
        snprintf(path, sizeof(path), "%s/%s", dir_name, file_names[i]);
        

        if (lstat(path, &file_state) < 0)
        {
            perror("lstat");
            continue;
        }

        if (show_inode)  // Print inode number if -i option is enabled
        {
            printf("%ld ", file_state.st_ino);
        }

        printf("%s ",get_permission(file_state));
        /*
        * prints the file's permissions by calling (get_permission function);
        */

        printf("%ld ",file_state.st_nlink);
        /*
        * prints the number of hard links of the file 
        */

        struct passwd *pw = getpwuid(file_state.st_uid);
        struct group *gr  = getgrgid(file_state.st_gid);
        printf("%s %s ", pw ? pw->pw_name : "unknown", gr ? gr->gr_name : "unknown");
        /*
        * retrieves and prints the owner's username and the group name of the file.
        */

        printf("%ld ", file_state.st_size);
        /*
        * prints the file size.
        */

        char time_buf[80];
        struct tm *timeinfo ;

        if (show_by_acs_time)
        {
            timeinfo = localtime(&file_state.st_atime);

        }else if (show_by_mod_time)
        {
           timeinfo = localtime(&file_state.st_ctime);

        }else
        {
            timeinfo = localtime(&file_state.st_mtime);
        }
        strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", timeinfo);
        printf("%s ", time_buf);
        /*
        * formats and prints the last modification time using local time and strftime.
        */
       if (show_color)
       {
            if (S_ISDIR(file_state.st_mode))
            {
                printf( COLOR_DIR "%s\n" COLOR_RESET,file_names[i]);

            }else if (S_ISLNK(file_state.st_mode))
            {
                printf( COLOR_LINK "%s\n" COLOR_RESET,file_names[i]);

            }else if (file_state.st_mode & S_IXUSR)
            {

                printf( COLOR_EXEC "%s\n" COLOR_RESET,file_names[i]);

            }else
            {
                printf( "%s\n",file_names[i]);
            }
        }
       /*
        * prints the file name with default --color option.
        */
    }
    for (int i = 0; i < file_count; i++)
    {
        free(file_list[i]);
    }
    

}




/* ************** Definition section End ************************ */



/* *******************************************************
   @User                 @Date              @time
   *******************************************************
   mohamed hamam         15sept2024         11:40 pm
   mohamed hamam         19sept2024         07:40 pm         
*/

