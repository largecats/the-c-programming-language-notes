/*
Exercise 8-4. The standard library function
int fseek(FILE *fp, long offset, int origin)
is identical to lseek except that fp is a file pointer instead of a file descriptor and return value is an int status, not a position.
Write fseek. Make sure that your fseek coordinates properly with the buffering done for the other functions of the library.
*/

/* 
http://www.cplusplus.com/reference/cstdio/fseek/
fseek: Sets the position indicator associated with the stream to a new position.
If successful, the function returns zero.
Otherwise, it returns non-zero value.
If a read or write error occurs, the error indicator (ferror) is set.

More comprehensive answers: https://clc-wiki.net/wiki/K%26R2_solutions:Chapter_8:Exercise_4
*/

#include <stdio.h>
#include <stdlib.h>
#include "../../../helper_functions.h"
#include "header.h"

FILE1 _iob1[OPEN_MAX];
int fseek1(FILE1 *fp, long offset, int origin);

int main() {
    FILE1 *fp = fopen1("chapter8/8.5/exercise_8-4/hello.txt","w");
    char *s = "hello";
    while (*s != '\0') {
        putc1(*s++, fp);
    }
    fseek1(fp, 10, 0);
    char *t = "world";
    while (*t != '\0') {
        putc1(*t++, fp);
    }
    fclose1(fp);
}

/*
$ gcc chapter8/8.5/exercise_8-4/main.c chapter8/8.5/exercise_8-4/fopen.c chapter8/8.5/exercise_8-4/fclose.c helper_functions.c -o chapter8/8.5/exercise_8-4/result.out

$ chapter8/8.5/exercise_8-4/result.out

# if fflushbuf is buffered: output in hello.txt: h         elloworld
# if not buffered: hello     world
*/

int fseek1(FILE1 *fp, long offset, int origin) {
    /* because fseek resets position, need to clear buffer first */
    if ((fp->flag %_UNBUF) == 0 && fp->base != NULL) {
        if (fp->flag & _READ) {
            fp->cnt = 0;
            fp->ptr = fp->base;
        }
        else if (fp->flag & _WRITE) {
            fflush1(fp);
        }
    }
    return lseek(fp->fd, offset, origin); /* same return code */
}