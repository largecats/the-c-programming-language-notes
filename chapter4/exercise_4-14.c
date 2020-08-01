/*
Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t. (Block structure will help.)
*/

#include <stdio.h>

#define swap(t, x, y) {t temp = x; x = y; y = temp;}
#define print_variable(expr) printf(#expr " = %d\n", expr)

int main() {
    int x, y;

    x = 1;
    y = 2;
    swap(int, x, y);
    print_variable(x);
    print_variable(y);
}