#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main() {
    minprintf("hello\n");
    int i = 5;
    minprintf("i = %d\n", i);
    double j = 5.0;
    minprintf("j = %f\n", j);
    char *s = "hello";
    minprintf("s = %s\n", s);
}

/*
$ gcc chapter7/7.3/minprintf.c -o chapter7/7.3/result.out

$ chapter7/7.3/result.out
hello
i = 5
j = 5.000000
s = hello
*/

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
    va_list ap; /* declare ap of type va_list to point to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt); /* make ap point to the 1st unnamed argument */
    for (p=fmt; *p; p++) {
        if (*p!='%') {
            putchar(*p);
            continue;
        }
        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++) {
                    putchar(*sval);
                }
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap); /* clean up */
}