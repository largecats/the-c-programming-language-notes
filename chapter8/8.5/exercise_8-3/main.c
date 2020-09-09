/*
Exercise 8-3. Design and write _flushbuf, fflush, and fclose.
*/

#include <stdio.h>
#include "../../../helper_functions.h"
#include "header.h"

int main() {
    ;
}

/* _flushbuf: write everything in a buffer to a file (represented by a file descriptor) and put c in buffer*/
int _flushbuf(int c, FILE1 *fp) {
    int bufsize, n;

    if ((fp->flag & (_WRITE|_EOF|_ERR)) != _WRITE) {
        return EOF;
    }
    if (fp->flag & _UNBUF) {
        /* file is not buffered */
        fp->ptr = fp->base = NULL;
        fp->cnt = 0;
        if (c == EOF) {
            return EOF;
        }
        n = write(fp->fd, &c, 1);
        bufsize = 1;
    }
    else {
        /* file is buffered */
        if (c != EOF) {
            *(fp)->ptr++ = c;
        }
        bufsize = (int) (fp->ptr - fp->base);
        n = write(fp->fd, fp->base, bufsize);
        fp->ptr = fp->base; /* reset pointer */
        fp->cnt = BUFSIZ - 1; /* reset number of available slots in buffer? */
    }
    if (n == bufsize) {
        return c;
    }
    else {
        return EOF; /* return EOF if error */
    }
}