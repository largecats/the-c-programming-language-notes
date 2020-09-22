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
*/
#include <stdio.h>
#include <stdlib.h>
#include "../../../helper_functions.h"
#include "header.h"

int main() {
    ;
}

int fseek(FILE1 *fp, long offset, int origin) {
    // TBD
    return lseek(fp->fd, offset, origin);
}