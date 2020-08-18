#include <stdio.h>

#define MAXLINE 100
#define print_variable(expr) printf(#expr " = %d\n", expr)
#define print_char(expr) printf(#expr " = %c\n", expr)
#define print_string(expr) printf(#expr " = %s\n", expr)

void print_array(int arr[]);
void print_float_array(double arr[]);
void swap(char s[], int i, int j);
void swap_pointer_version(char *v[], int i, int j);
int getch(void);
void ungetch(int c);

/* memory allocator */
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf; /* pointer to the next free position, initialized to the first position in allocbuf */

char *alloc(int n);
void afree(char *p);

int getline_pointer_version(char *, int);

void print_char_with_visible_blanks(char c);
