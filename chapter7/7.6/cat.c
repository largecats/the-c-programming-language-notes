#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "../../helper_functions.h"

/* cat: concatenate files, version 2 */
int main(int argc, char *argv[]) {
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0]; /* get program name to print along with error */

    if (argc == 1) { /* no args, copy standard input */
        filecopy(stdin, stdout);
    }
    else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv); /* print error in stderr */
                exit(1);
            }
            else {
                filecopy(fp, stdout); /* print file to stdout */
                fclose(fp);
            }
        }
    }
    if (ferror(stdout)) { /* if there's any error in the stdout stream, write error to stderr */
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp) {
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
    }
}

/*
$ gcc chapter7/7.6/cat.c -o chapter7/7.6/result.out

$ chapter7/7.6/result.out chpater7/7.6/hello.txt
hello hello

$ chapter7/7.6/result.out chpater7/7.6/hello1.txt
chapter7/7.6/result.out: can't open chapter7/7.6/hello1.txt
*/