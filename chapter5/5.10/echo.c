#include <stdio.h>
#include "../../helper_functions.h"

/* echo command-line arguments */
int main(int argc, char *argv[]) { /* argv is a pointer to the head of an array of pointers */
    print_variable(argc);
    while (--argc > 0) {
        printf("%s%s", *++argv, (argc > 1)? " ": "");
    }
    printf("\n");
    return 0;
}

/*
$ gcc chapter5/5.10/echo.c -o chapter5/5.10/result.out
$ chapter5/5.10/result.out hello world
argc = 3
hello world
*/