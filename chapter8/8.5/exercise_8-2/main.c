/*
Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit operations. Compare code size and execution
speed.
*/

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include "../../../helper_functions.h"

#define N 1000
#define PERMS 0666 /* default permission when creating files, RW for owner, group, others */
#define OPEN_MAX 20

typedef struct _iobuf1 {
    int cnt;
    char *ptr;
    char *base;
    int flag;
    int fd;
} FILE1;
FILE1 _iob1[OPEN_MAX];

enum _flags {
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

typedef struct flags {
    unsigned int _READ: 1;
    unsigned int _WRITE: 1;
    unsigned int _UNBUF: 1;
    unsigned int _EOF: 1;
    unsigned int _ERR: 1;
} FLAG;

typedef struct _iobuf2 {
    int cnt;
    char *ptr;
    char *base;
    FLAG flag;
    int fd;
} FILE2;
FILE2 _iob2[OPEN_MAX];

int _fillbuf1(FILE1 *fp);
FILE1 *fopen1(char *name, char *mode);
void fclose1(FILE1 *fp);

int _fillbuf2(FILE2 *fp);
FILE2 *fopen2(char *name, char *mode);
void fclose2(FILE2 *fp);

#define getc1(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++: _fillbuf1(p))
#define getc2(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++: _fillbuf2(p))

int main(){
    // for (int i=0; i<N; i++) {
    FILE1 *fp1 = fopen1("chapter8/8.5/exercise_8-2/hello1.txt","r");
    if (fp1 != NULL) {	
        char c1;
        while ((c1=getc1(fp1)) != EOF) {
            putchar(c1);
        }
    }
    else {
        printf("Failed to open file");
    }
    // fclose1(fp1);
    // }
    
    // for (int i=0; i<N; i++) {
    FILE2 *fp2 = fopen2("chapter8/8.5/exercise_8-2/hello2.txt","r");
    if (fp2 != NULL) {	
        char c2;
        while ((c2=getc2(fp2)) != EOF) {
            putchar(c2);
        }
    }
    else {
        printf("Failed to open file");
    }
    // fclose2(fp2);
    // }
	
	return 0;
}

/*
$ gcc chapter8/8.5/exercise_8-2/main.c helper_functions.c -o chapter8/8.5/exercise_8-2/result.out

$ chapter8/8.5/exercise_8-2/result.out
hello1
hello2
*/

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

// void fclose1(FILE1 *fp) {
//     close(fp->fd);
//     fp = NULL;
// }

/* fopen2: open file, return file ptr */
FILE2 *fopen2(char *name, char *mode) {
    int fd;
    FILE2 *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
        return NULL;
    }
    for (fp = _iob2; fp < _iob2 + OPEN_MAX; fp++) { /* _iob is the start of the array of file pointers */
        if (!fp->flag._READ && !fp->flag._WRITE) {
            break; /* found free slot */
        }
    }
    if (fp >= _iob2 + OPEN_MAX) {
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
    switch (*mode) {
        case 'r':
            fp->flag._READ = 1;
            break;
        case 'w':
            fp->flag._WRITE = 1;
            break;
        default:
            break;
    }
    return fp;
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

// void fclose2(FILE2 *fp) {
//     close(fp->fd);
//     fp = NULL;
// }