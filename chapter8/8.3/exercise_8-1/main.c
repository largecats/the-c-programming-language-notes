/*
Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open, and close instead of their standard library
equivalents. Perform experiments to determine the relative speeds of the two versions.
*/

#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include "../../../helper_functions.h"

#define N 1000


/* cat: concatenate files */
int main(int argc, char *argv[]) {
    
    clock_t start, end;
    double cpu_time_used1, cpu_time_used2;

    start = clock();
    for (int i=0; i<N; i++) {
        cat1(argc, argv);
    }
    end = clock();
    cpu_time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC / N;
    
    start = clock();
    for (int i=0; i<N; i++) {
        cat2(argc, argv);
    }
    end = clock();
    cpu_time_used2 = ((double) (end - start)) / CLOCKS_PER_SEC / N;

    printf("cat1: %f\n", cpu_time_used1);
    printf("cat2: %f\n", cpu_time_used2);
    return 0;
}

/* cat1: concatenating files using standard library functions */
int cat1(int argc, char *argv[]) {
    FILE *fp;
    void filecopy1(FILE *, FILE *);

    if (argc == 1) /* no args, copy standard input */ {
        filecopy1(stdin, stdout);
    }
    else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("cat1: can't open %s\n", *argv);
                return 1;
            }
            else {
                filecopy1(fp, stdout);
                fclose(fp);
            }
        }
    }
    return 0;
}

/* filecopy1: copy file ifp to file ofp */
void filecopy1(FILE *ifp, FILE *ofp) {
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
    }
}

/* cat2: concatenate files using read, write, open, close */
int cat2(int argc, char *argv[]) {
    int fd;
    void filecopy2(int, int);

    if (argc == 1) { /* no args, copy standard input */
        filecopy2(0, 1);
    }
    else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY, 0)) < 0) {
                printf("cat2: failed to open %s with errno %d\n", *argv, errno);
                return 1;
            }
            else {
                filecopy2(fd, 1); /* print file to stdout */
                close(fd);
            }
        }
    }
}


/* filecopy2: copy file ifd to file ofd */
void filecopy2(int ifd, int ofd) {
    int c;

    while (read(ifd, &c, 1) > 0) {
        write(ofd, &c, 1);
    }
}


/*
$ gcc chapter8/8.3/exercise_8-1/main.c -o chapter8/8.3/exercise_8-1/result.out

$ chapter8/8.3/exercise_8-1/result.out chapter8/8.3/exercise_8-1/hello.txt
do you read me
...
do you read me
cat1: 0.000484
cat2: 0.001141 // standard library is faster

$ chapter8/8.3/exercise_8-1/result.out // no loop to measure time
knock knock
knock knock
hello Neo
hello Neo
*/