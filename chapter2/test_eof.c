#include <stdio.h>

int main () {
    int c;

    printf("Please enter Ctrl-D...\n");
    c = getchar();
    printf("read Ctrl-D %d\n", c);

    clearerr(stdin); // on some machines, clearerr(stdin) is not needed to get it to go pass -1 and continue reading the next input

    c = getchar();
    printf("read another character %d\n", c);

    return 0;
}

/*
https://github.com/microsoft/WSL/issues/3421
$ gcc chapter2/test_eof.c -o result.out
$ chapter2/result.out
Please enter Ctrl-D...
read Ctrl-D -1
a
read another character 97
*/