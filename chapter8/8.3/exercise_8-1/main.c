/*
Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open, and close instead of their standard library
equivalents. Perform experiments to determine the relative speeds of the two versions.
*/

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include "../../../helper_functions.h"

/* cat: concatenate files, version 1 */
int main(int argc, char *argv[]) {
    int fd;
    void filecopy(int, int);

    if (argc == 1) { /* no args, copy standard input */
        filecopy(0, 1);
    }
    else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) < 0) {
                printf("cat: failed to open %s with errno %d\n", *argv, errno);
                return 1;
            }
            else {
                filecopy(fd, 1); /* print file to stdout */
                close(fd);
            }
        }
    }
    return 0;
}

/* filecopy: copy file ifd to file ofd */
void filecopy(int ifd, int ofd) {
    int c;

    while (read(ifd, &c, 1) > 0) {
        write(ofd, &c, 1);
    }
}

/*
$ gcc chapter8/8.3/exercise_8-1/main.c -o chapter8/8.3/exercise_8-1/result.out

$ chapter8/8.3/exercise_8-1/result.out chapter8/8.3/exercise_8-1/hello.txt
do you read me

$ chapter8/8.3/exercise_8-1/result.out
knock knock
knock knock
hello Neo
hello Neo
*/