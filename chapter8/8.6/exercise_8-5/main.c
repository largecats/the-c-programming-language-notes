/*
Exercise 8-5. Modify the fsize program to print the other information contained in the inode entry.
*/

#include <stdio.h>
#include <string.h>
// #include "syscalls.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "dirent.h"

void fsize(char *);

/* print file name */
int main(int argc, char **argv) {
    if (argc == 1) { /* no arg supplied, print for current directory */
        fsize(".");
    }
    else {
        while (--argc > 0) {
            fsize(*++argv);
        }
    }
    return 0;
}

/*
$ gcc chapter8/8.6/main.c chapter8/8.6/exercise_8-5/dir_ops.c chapter8/8.6/exercise_8-5/fsize.c helper_functions.c -o chapter8/8.6/exercise_8-5/result.out

$ chapter8/8.6/exercise_8-5/result.out
File: /.../fun/languages/c/
Device: 14
Inode number: 1407374884317397
Mode bits: 16895
Number of links: 1
Owner userid: 1000
Ownder gorupid: 1000
Size: 4096
Access: 2020-09-26 17:37:15
LModify: 2020-09-26 15:37:08
Change: 2020-09-26 15:37:08
*/