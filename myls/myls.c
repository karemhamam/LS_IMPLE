/* *******************************************************
   * @File                 : myls.c
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
#include <time.h>      // for time formatting.
#include <sys/ioctl.h> //for ioctl to get terminal width
#include "myls.h"      // includes the declaration of do_ls.
#include "option_l.h"  // for the declaration of the do_ls_optoion_l function.

/* **************** Include section End *************** */


/* **************** Declaration section start *************** */

char program_name[MAX_NAME_SIZE]; // array to store the name of myls (argv[0]).

int show_long_format  = 0 ; // for the -l option. 
int show_hidden_files = 0 ; // for the -a option.
int show_by_mod_time  = 0 ; // for the -t option.
int show_by_acs_time  = 0 ; // for the -u option.
int show_by_last_mod  = 0 ; // for the -c option.
int show_inode        = 0 ; // for the -i option.
int show_disable_sort = 0 ; // for the -f option.
int show_table        = 0 ; // for the -1 option.
int show_directory    = 0 ; // for the -d option.
int show_color        = 1 ; // 1 to enable color by default.


/* **************** Declaration section End ****************** */


/* **************** main section start ****************** */

int main (int argc , char *argv[])
{
    int opt;
    char *dir_name = "." ;

    strcpy(program_name,argv[0]); 


    while ((opt = getopt(argc, argv ,"latucifd1")) != -1 )
    {
        switch(opt)
        {
            case 'l' :
                show_long_format  = 1  ;
                break;

            case 'a' :
                show_hidden_files = 1 ;
                break;
            case 't' :
                show_by_mod_time  = 1 ;
                break; ;
            case 'u' :
                show_by_acs_time  = 1 ;
                break;
            case 'c' :
                show_by_last_mod = 1 ;
                break;
            case 'i' :
                show_inode       = 1 ;
                break;
            case 'f' :
                show_disable_sort = 1 ;
                break;
            case '1' :
                show_table        = 1 ;
                break;
            case 'd' :
                show_directory    = 1 ;
                break;
            default:
                fprintf(stderr, "Usage: %s [-opt.] [directory]\n",argv[0]);
                exit(EXIT_FAILURE);
        }
        
    }

    if (optind < argc)
    {
        dir_name = argv[optind];
    }else
    {
        dir_name = ".";
    }

    if (show_long_format)
    {
        if (show_directory)
        {
            if (argc == 2 )
            {
                do_ls_option_l(".");
            }else 
            {
                int i = 1 ;
                while(++i < argc)
                {
                    if (check_for_dir(argv[i]))
                    {
                        do_ls_option_l(argv[i]);
                    }
                } 
            }
            
        }else if (argc == 2 )
        {
            do_ls_option_l(dir_name);
            
        }else
        {
            int j = 1 ; 
            while (++j < argc) // Check if multiple directories were provided after options
            {
            
                if (check_for_dir(argv[j]))
                {
                    if (argc > 3 )
                    {
                        printf("%s :\n",argv[j]);
                        do_ls_option_l(argv[j]);
                    }else
                    {
                        do_ls_option_l(argv[j]);
                    }
                }
            }
            
        }

    }else
    {
        if (show_directory)
        {
            if (argc == 2 )
            {
                if (check_for_dir("."))
                {
                    printf(".\n");
                }
            }else
            {
                int i = 1 ;
                while(++i < argc)
                {
                    if (check_for_dir(argv[i]))
                    {
                        printf("%s\n", argv[i]);
                    }
                }
            }
        }else
        if ((argc == 1) || (argc == 2 && show_hidden_files) ||(argc == 2 && show_by_mod_time ) || (argc == 2 && show_by_acs_time ) || (argc == 2 && show_by_last_mod ) || (argc == 2 && show_inode ) || (argc == 2 && show_disable_sort ) || (argc == 2 && show_table) ) // list the content of the current working directory
        {
            do_ls(".");
        }else
        {
            int i = 1;
            while (++i < argc ) // start form 1 , because 0 is for the program name.
            { 
                if ( check_for_dir(argv[i]))  // for being like the original ls.
                {
                    if (argc > 2 ) // just for being like the original ls .
                    {
                        printf("%s :\n" , argv[i]);
                        do_ls(argv[i]);
                    }else
                    {
                        do_ls(argv[i]);
                    }

                }else{};

            }
        
        }
    }
    


   return 0;
}

/* **************** main section End ****************** */


/* **************** Definition section start *************** */

int check_for_dir(char *dir)
{
    int error_state = 1 ;
    struct dirent *entry;
    DIR *dp = opendir (dir); // opendir to open the directory specified by the dir parameter.

    if (dir == "-l" || dir == "-a"|| dir == "-u" || dir == "-t" || dir == "-c" || dir == "-d" || dir == "-1" || dir == "-f" || dir == "-i" )
    {
        error_state = 0 ;

    }else if ( dp == NULL )
    {
        error_state = -1 ;
        fprintf(stderr,"%s: cannot access '%s': No such file or directory\n",program_name,dir);
        return error_state;
    }

    return error_state ;
}



void do_ls(char *dir)
{
    struct dirent *entry;
    struct stat stat_1 ;
    
    DIR *dp = opendir(dir); // opendir to open the directory specified by the dir parameter.

    if (dp == NULL)
    {
        perror("opendir");
        exit(1);
    }

    char *file_names[MAX_FILE_SIZE]; // array to store the name of the files.
    int file_count = 0 ;             // counter to store the number of files.

    errno = 0 ;

    while ( ( entry = readdir(dp) ) != NULL) // each entry represent a file.
    {
        if (entry == NULL && errno != 0 )
        {
            perror("readdir failed");
            exit(1);
        }else
        { 
            if(entry->d_name[0] == '.' && !show_hidden_files && !show_disable_sort) // filter the hidden files
            {
                continue;
            }else
            {
                file_names[file_count] = strdup(entry->d_name);
                if (file_names[file_count] == NULL)
                {
                    fprintf(stderr , "Memory allocation failed for file name\n");
                    exit(1);
                }
                file_count++;

                if (file_count >= MAX_FILE_SIZE )
                {
                    fprintf(stderr,"Too much files in the directoy !!\n");
                    exit(1);
                }
            }
            
        }


    }
    closedir(dp);

    if (!show_disable_sort)
    {
        if ( show_by_last_mod )
        {
            sort_by_last_mod_time(file_names , file_count , dir);

        }else if (show_by_acs_time)
        {
            sort_by_acs_time(file_names, file_count , dir);

         }else if (show_by_mod_time)
        {
            sort_by_last_mod_time(file_names, file_count, dir);
        }
        else
        {
            bubble_sort(file_names, file_count);
        }
    }




    int max_len = 0;
    int i = 0 ;

    for ( i = 0; i < file_count; i++) 
    {
        int len = strlen(file_names[i]);

        if (len > max_len) 
        {
            max_len = len;
        }
    }

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminal_width = w.ws_col; 

    
    int cols = terminal_width / (max_len + 2); // 2 for padding
    if (cols == 0) cols = 1;                   // Fallback to 1 column if terminal width is too small
    /*
    * Calculate how many columns can fit based on terminal width and file name length
    */

    int rows = (file_count + cols - 1) / cols; // ceiling division to get number of rows
    /*
      Calculate how many rows are needed based on the number of files and columns
    */
    // for ( i = 0 ; i < file_count ; i++)
    // {
    //     char path_1[MAX_FILE_SIZE]; 

    //     snprintf(path_1 , sizeof(path_1) , "%s/%s" , dir , file_names[i]);

    //     if (lstat(path_1, &stat_1) == -1)
    //     {
    //         perror("lstat");
    //         continue;;
    //     }
    // }


    if (!show_table)
    {
        for (int row = 0; row < rows; row++)
        {
            for (int col = 0; col < cols; col++)
            {
                int index = row + col * rows; 

                if (index < file_count )
                {
                    char path_1[MAX_FILE_SIZE];
                    
                    snprintf(path_1 , sizeof(path_1) , "%s/%s" , dir , file_names[index]);

                    if (lstat(path_1, &stat_1) == -1)
                    {
                        perror("lstat");
                        continue;;
                    }
                    if (show_inode)
                    {
                        printf("%ld ", (long)stat_1.st_ino);
                    }
                    if (S_ISDIR(stat_1.st_mode))
                    {
                        printf(COLOR_DIR "%-*s" COLOR_RESET, max_len + 2, file_names[index]);
                    }else if(S_ISLNK(stat_1.st_mode))
                    {
                        printf(COLOR_LINK "%-*s" COLOR_RESET, max_len + 2, file_names[index]);
                    }else if (stat_1.st_mode & S_IXUSR )
                    {
                        printf(COLOR_EXEC "%-*s" COLOR_RESET, max_len + 2, file_names[index]);
                    }else
                    {
                        printf(COLOR_RESET "%-*s" COLOR_RESET, max_len + 2, file_names[index]);
                    }
 

                }
            }
            printf("\n"); 
        }
    }
    else
    {
        for (int i = 0; i < file_count; i++)
        {
            printf("%s\n", file_names[i]);
        }
    }



    for (i = 0 ; i < file_count ; i++)
    {
        free(file_names[i]); //free the allocated memory for the file_names array.
    }

}

/* ************** Definition section End ************************ */


/* *******************************************************
   @User                 @Date              @time
   *******************************************************
   mohamed hamam         12sept2024         08:15 pm
   mohamed hamam         19sept2024         07:40 pm          
*/

