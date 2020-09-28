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
extern FILE1 _iob1[OPEN_MAX];

enum _flags {
    _READ = 01,
    _WRITE = 02,
    _UNBUF = 04,
    _EOF = 010,
    _ERR = 020
};

int _fillbuf1(FILE1 *fp);
int _flushbuf1(int x, FILE1 *fp);
FILE1 *fopen1(char *name, char *mode);
int fclose1(FILE1 *fp);

#define getc1(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++: _fillbuf1(p))
#define putc1(x, p) (--(p)->cnt >= 0? *(p)->ptr++ = (x): _flushbuf1((x), p))
/* putc is an output function:
int putc(int c, FILE *fp)
putc writes the character c to the file fp and returns the character written, or EOF if an error occurs. 
*/