# myls - Custom File Listing Utility

## Overview

**myls**
 is a custom implementation of the `ls` command with various options, including support for long format listings, sorting by access time, inode display, single-column listing, and colorized output. It is designed to replicate the functionality of the GNU `ls` command with additional custom features.

## Features

- **Long Format Listing (`-l`)**: Displays detailed information about files such as permissions, number of hard links, owner, group, size, and modification time.

 ![Screenshot from 2024-09-19 20-27-24](https://github.com/user-attachments/assets/187e070e-59d6-43c7-847a-bafe4abb9b49)

- **Sort by Access Time (`-u`)**: Sorts files by their last access time.

  ![Screenshot from 2024-09-19 20-28-04](https://github.com/user-attachments/assets/785f262b-cb03-46dc-99fb-a57849f09e10)

- **Sort by Modification Time (`-t`)**: Sorts files by their last modification time.

  ![Screenshot from 2024-09-19 20-27-54](https://github.com/user-attachments/assets/7f3b4b08-e58a-4ec5-ab68-02d634d0986a)

- **Display Inode Numbers (`-i`)**: Displays the inode number of each file.

  ![Screenshot from 2024-09-19 20-29-37](https://github.com/user-attachments/assets/113f37e9-7050-4b0c-9f81-d0d13c690b10)

- **Show Hidden Files (`-a`)**: Includes hidden files (files that start with a dot `.`).

![Screenshot from 2024-09-19 20-28-29](https://github.com/user-attachments/assets/e80f4152-892e-4db6-ac9f-ab7e216503a7)

- **Directory Listing (`-d`)**: Displays directory names, not their contents.

  ![Screenshot from 2024-09-19 20-29-04](https://github.com/user-attachments/assets/8eca9eb5-74c3-4153-a652-c53bdba0fc2f)

- **Disable Sorting (`-f`)**: Disables sorting and lists files as they appear in the directory.

![Screenshot from 2024-09-19 20-28-45](https://github.com/user-attachments/assets/cb3cab15-d349-4ae1-8f32-5a6aab0cd966)

- **Color Output (`--color`)**: Displays directories, symbolic links, and executables in different colors by default.

  ![WhatsApp Image 2024-09-19 at 20 38 58_0b710c14](https://github.com/user-attachments/assets/b7b50b51-3f88-4ae9-8805-eeac78ad2eb6)

- **Single-Column Listing (`-1`)**: Forces output to display one file per line.

  ![Screenshot from 2024-09-19 20-29-59](https://github.com/user-attachments/assets/793309c6-7363-4218-be20-4af09dd90048)

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
`gcc -o myls myls.c option_l.c -sort.c`

## video 
here is a link to a short video showing  myls capabilities ->(https://drive.google.com/file/d/1FtMazUkHlfHp3bIAKQ-AB44U2jw5M1vb/view?usp=sharing).

## Development
The project is modular, with separate files handling different options. The following files are crucial to the functioning of myls:

### myls.c:
The main file for handling command-line arguments and invoking the appropriate options.

### option_l.c: 
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


