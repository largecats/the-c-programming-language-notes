#include <stdio.h>
#include <string.h>
#include "../../helper_functions.h"

/* find: print lines that match pattern from 1st arg */
int main(int argc, char *argv[]) {
    char line[MAXLINE];
    long lineno = 0;
    int c, except = 0, number = 0, found = 0;

    while (--argc > 0 && (*++argv)[0] == '-') {
        while (c = *++argv[0]) {
            switch (c) {
                case 'x':
                    except = 1;
                    break;
                case 'n':
                    number = 1;
                    break;
                default:
                    printf("find: illegal options %c\n", c);
                    argc = 0;
                    found = -1;
                    break;
            }
        }
    }
    if (argc != 1) {
        printf("Usage: find -x -n pattern\n");
    }
    else {
        while (getline1(line, MAXLINE) > 0) {
            lineno++;
            if ((strstr(line, *argv) != NULL) != except) {
                if (number) {
                    printf("%ld:", lineno);
                }
                printf("%s", line);
                found++;
            }
        }
    }
    return found;
}

/*
$ gcc chapter5/5.10/match_pattern.c helper_functions.c -o chapter5/5.10/result.out

$ chapter5/5.10/result.out hello
hello world
hello world
hello Neo
hello Neo
knock knock

$ chapter5/5.10/result.out -xn hello
hello world
knock knock
2:knock knock
*/