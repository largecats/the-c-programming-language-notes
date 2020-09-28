/*
Exercise 8-3. Design and write _flushbuf, fflush, and fclose.
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../../helper_functions.h"
#include "header.h"

FILE1 _iob1[OPEN_MAX];

int main() {
    FILE1 *fp = fopen1("chapter8/8.5/exercise_8-3/hello.txt","w");
    char *s = "hello";
    while (*s != '\0') {
        putc1(*s++, fp);
    }
    fclose1(fp);
}

/*
$ gcc chapter8/8.5/exercise_8-3/main.c chapter8/8.5/exercise_8-3/fopen.c chapter8/8.5/exercise_8-3/fclose.c helper_functions.c -o chapter8/8.5/exercise_8-3/result.out

$ chapter8/8.5/exercise_8-3/result.out

# output in hello.txt: hello
*/