#include <stdio.h>
#include "../../helper_functions.h"

/* cat: concatenate files, version 1 */
int main(int argc, char *argv[]) {
    FILE *fp;
    void filecopy(FILE *, FILE *);

    if (argc == 1) { /* no args, copy standard input */
        filecopy(stdin, stdout);
    }
    else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                print_string(*argv);
                printf("cat: failed to open %s\n", *argv);
                return 1;
            }
            else {
                filecopy(fp, stdout); /* print file to stdout */
                fclose(fp);
            }
        }
    }
    return 0;
}

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp) {
    int c;

    while ((c = getc(ifp)) != EOF) {
        putc(c, ofp);
    }
}

/*
$ gcc chapter7/7.5/cat.c -o chapter7/7.5/result.out

$ chapter7/7.5/result.out "/mnt/c/users/xiaolf/fun/languages/c/the-c-programming-language-notes/chpater7/7.5/hello.txt“
*/