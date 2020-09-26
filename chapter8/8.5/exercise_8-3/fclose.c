#include <stdio.h>
#include <stdlib.h>
#include "../../../helper_functions.h"
#include "header.h"

/* _flushbuf1: write everything in the buffer to a file (represented by a file descriptor) and put c in buffer*/
int _flushbuf1(int c, FILE1 *fp) {
    int bufsize, n;

    if ((fp->flag & (_WRITE|_EOF|_ERR)) != _WRITE) {
        return EOF;
    }
    if (fp->base == NULL && ((fp->flag & _UNBUF) == 0)) {
        /* no buffer yet */
        if ((fp->base = malloc(BUFSIZ)) == NULL) {
            /* cannot allocate buffer */
            fp->flag |= _UNBUF; /* use unbuffered write, i.e., write one character at a time */
        }
        else {
            fp->ptr = fp->base;
            fp->cnt = BUFSIZ - 1;
        }
    }
    if (fp->flag & _UNBUF) {
        // printf("not buffered\n");
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
        // printf("buffered\n");
        /* file is buffered */
        if (c != EOF) {
            *(fp)->ptr++ = c;
        }
        bufsize = (int) (fp->ptr - fp->base);
        // printf("writing\n");
        n = write(fp->fd, fp->base, bufsize);
        fp->ptr = fp->base; /* reset pointer */
        fp->cnt = BUFSIZ - 1; /* reset number of available slots in buffer? */
    }
    if (n == bufsize) {
        return c;
    }
    else {
        /* "the return value is the number off bytes written; an error has occurred if this isn't equal to the number requested */
        fp->flag |= _ERR;
        return EOF; /* return EOF if error */
    }
}

/* fflush1: "clear (or flush) the output buffer and move the buffered data to console (in case of stdout) or disk (in case of file output stream)" */
/*
 For output streams, fflush() forces a write of all user-space
buffered data for the given output or update stream via the stream's
underlying write function.

For input streams associated with seekable files (e.g., disk files,
but not pipes or terminals), fflush() discards any buffered data that
has been fetched from the underlying file, but has not been consumed
by the application.

The open status of the stream is unaffected.

If the stream argument is NULL, fflush() flushes all open output
streams.
https://man7.org/linux/man-pages/man3/fflush.3.html
*/
int fflush1(FILE1 *fp) {
    if (fp == NULL) {
        /* stream argument (recall that all streams are FILE objects) is NULL, flush all open output streams */
        FILE1 *fp1;
        for (fp1 = _iob1; fp1 < _iob1 + OPEN_MAX; fp1++) {
            if (fflush1(fp1) == -1) {
                return -1;
            }
        }
    }
    else {
        /* flush only the stream represented by fp */
        if ((fp->flag & _WRITE) == 0) {
            return -1;
        }
        _flushbuf1(EOF, fp);
        if (fp->flag & _ERR) {
            return -1;
        }
    }
}

/* fclose1: */
int fclose1(FILE1 *fp) {
    if (fp == NULL) {
        return -1;
    }
    fflush1(fp);
    fp->cnt = 0;
    fp->ptr = NULL;
    if (fp->base != NULL) {
        /* if a buffer was allocated, free its storage */
        free(fp->base);
        fp->base = NULL;
    }
    fp->flag = 0;
    int fdTemp = fp->fd;
    fp->fd = -1; /* file descriptor is positive */
    return close(fdTemp);
}