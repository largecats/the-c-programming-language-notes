#include <stdio.h>

#define MAXLINES 5000
#define MAXLEN 1000 /* max length of any input line */
#define MAXFIELDS 10

extern char *lineptr[MAXLINES];
extern int fields[MAXFIELDS][2]; // 2D array to store the start and end of each field
extern int fieldArgs[MAXFIELDS][4]; // 2D array to store arguments for each field, in the order -n -r -f -d
extern int n, r, f, d; // numeric, reverse, fold, directory
extern int fieldStart, fieldEnd;