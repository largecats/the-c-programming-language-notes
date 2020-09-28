#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "header.h"

/* _fillbuf1: allocate the fill input buffer */
int _fillbuf1(FILE1 *fp) {
    int bufsize;

    if ((fp->flag&(_READ|_EOF|_ERR)) != _READ) {
        return EOF;
    }
    bufsize = (fp->flag & _UNBUF)? 1: BUFSIZ;
    if (fp->base == NULL) { /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF; /* can't get buffer */
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag |= _EOF;
        }
        else {
            fp->flag |= _ERR;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}

/* _fillbuf2: allocate the fill input buffer */
int _fillbuf2(FILE2 *fp) {
    int bufsize;

    if ((!fp->flag._READ) | fp->flag._EOF | fp->flag._ERR) {
        return EOF;
    }
    bufsize = (fp->flag._UNBUF)? 1: BUFSIZ;
    if (fp->base == NULL) { /* no buffer yet */
        if ((fp->base = (char *) malloc(bufsize)) == NULL) {
            return EOF; /* can't get buffer */
        }
    }
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0) {
        if (fp->cnt == -1) {
            fp->flag._EOF = 1;
        }
        else {
            fp->flag._ERR = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}
