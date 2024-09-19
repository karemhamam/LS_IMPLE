# myls - Custom File Listing Utility

## Overview

**myls**
 is a custom implementation of the `ls` command with various options, including support for long format listings, sorting by access time, inode display, single-column listing, and colorized output. It is designed to replicate the functionality of the GNU `ls` command with additional custom features.

## Features

- **Long Format Listing (`-l`)**: Displays detailed information about files such as permissions, number of hard links, owner, group, size, and modification time.

- **Sort by Access Time (`-u`)**: Sorts files by their last access time.

- **Sort by Modification Time (`-t`)**: Sorts files by their last modification time.

- **Display Inode Numbers (`-i`)**: Displays the inode number of each file.

- **Show Hidden Files (`-a`)**: Includes hidden files (files that start with a dot `.`).

- **Directory Listing (`-d`)**: Displays directory names, not their contents.

- **Disable Sorting (`-f`)**: Disables sorting and lists files as they appear in the directory.

- **Color Output (`--color`)**: Displays directories, symbolic links, and executables in different colors by default.

- **Single-Column Listing (`-1`)**: Forces output to display one file per line.

## Command Line Options

The following options are supported by **myls**:

| Option        | Description                                                                 |
|---------------|-----------------------------------------------------------------------------|
| `-l`          | Displays files in long format, showing additional metadata like permissions |
| `-u`          | Sorts files by access time instead of modification time                     |
| `-t`          | Sorts files by modification time (newest first)                             |
| `-a`          | Lists all files, including hidden files (those starting with `.`)           |
| `-i`          | Displays the inode number for each file                                     |
| `-d`          | Lists directory names instead of their contents                             |
| `-f`          | Disables sorting, lists files as they appear in the directory               |
| `--color`     | Displays output with colored directories, symbolic links, and executables   |
| `-1`          | Forces the output to list files one per line                                |

## Usage

### Basic Usage

To list the contents of a directory:


## Installation
To compile the myls utility:

Clone the repository or download the source code->(https://github.com/karemhamam/LS_IMPLE/tree/master)

Compile the source code using the following command:
gcc -o myls myls.c option_l.c -sort.c

## video 
here is short video of myls->().

## Development
The project is modular, with separate files handling different options. The following files are crucial to the functioning of myls:

### myls.c:
The main file for handling command-line arguments and invoking the appropriate options.

#### option_l.c: 
Handles the long-format listing (-l) and other related options.

### sort.c: 
file that have the implementation of all sorting functions.

## Future Improvements
The following features are planned for future releases:

### Recursive Listing (-R): 
List files in all subdirectories.

### Sorting by File Size (-S):
Sort files by size.

### Human-Readable Sizes (-h): 
Show file sizes in human-readable formats (KB, MB, GB).


## Contribution
If you would like to contribute to myls, feel free to fork the repository and submit a pull request. For major changes, please open an issue first to discuss what you would like to change.

## License
(mahamedhamam15@gmail.com)


