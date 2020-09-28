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
extern FILE2 _iob2[OPEN_MAX];

int _fillbuf1(FILE1 *fp);
FILE1 *fopen1(char *name, char *mode);
int fclose1(FILE1 *fp);

int _fillbuf2(FILE2 *fp);
FILE2 *fopen2(char *name, char *mode);
int fclose2(FILE2 *fp);

#define getc1(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++: _fillbuf1(p))
#define getc2(p) (--(p)->cnt >= 0 ? (unsigned char) *(p)->ptr++: _fillbuf2(p))