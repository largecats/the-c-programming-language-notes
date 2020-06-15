#include <stdio.h>

main() {
    int x = 1;
    static int y = 2 * x;
    printf("%d", y);
}