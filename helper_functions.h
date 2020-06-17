#include <stdio.h>

#define MAXLINE 100
#define print_variable(expr) printf(#expr " = %d\n", expr)
#define print_char(expr) printf(#expr " = %c\n", expr)

void print_string(char s[]);
void print_array(int arr[]);
void print_float_array(double arr[]);
void swap(char s[], int i, int j);
// int getch(void);
// void ungetch(int c);

/* memory allocator */
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf; /* pointer to the next free position, initialized to the first position in allocbuf */

char *alloc(int n);
void afree(char *p);

// int getline(char [], int);
int getline_pointer_version(char *, int);
void swap_pointer(char *s[], int i, int j);

void print_char_with_visible_blanks(char c);
