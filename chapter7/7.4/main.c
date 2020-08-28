#include <stdio.h>

int main() {
    double sum, v;

    sum = 0;
    while (scanf("%lf", &v) == 1) {
        /* as long as scanf reads one successfully matched and assigned input item */
        printf("\t%.2f\n", sum += v);
    }
    return 0;
}

/*
$ gcc chapter7/7.4/main.c -o chapter7/7.4/result.out

$ chapter7/7.4/result.out
1
        1.00
2
        3.00
-1
        2.00
*/