#include <stdio.h>
#include <fcntl.h>

int read(int fd, char *buf, int n);
int write(int fd, char *buf, int n);

int open(char *name, int flags, int perms);
int creat(char *name, int perms);

long lseek(int fd, long offset, int origin);