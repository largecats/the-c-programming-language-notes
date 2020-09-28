#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include "header.h"

/* fopen1: open file, return file ptr */
FILE1 *fopen1(char *name, char *mode) {
    int fd;
    FILE1 *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }
    for (fp = _iob1; fp < _iob1 + OPEN_MAX; fp++) { /* _iob is the start of the array of file pointers */
        if ((fp->flag & (_READ | _WRITE)) == 0) {
            break; /* found free slot */
        }
    }
    if (fp >= _iob1 + OPEN_MAX) {
        return NULL;
    }

    if (*mode == 'w') {
        fd = creat(name, PERMS);
    }
    else if (*mode == 'a') {
        if ((fd = open(name, O_WRONLY, 0)) == -1) {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    }
    else {
        fd = open(name, O_RDONLY, 0);
    }
    if (fd == -1) { /* couldn't access name */
        return NULL;
    }
    fp->fd =fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r')? _READ: _WRITE;
    return fp;
}
