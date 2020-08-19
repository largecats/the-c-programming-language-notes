/*
Exercise 1-5. Modify the temperature conversion program to print the table in reverse order, 
that is, from 300 degrees to 0.
*/

#include <stdio.h>

int main()
{
    int fahr;

    for (fahr = 300; fahr >= 0; fahr = fahr - 20) {
    // for (fahr = 0; fahr <= 300; fahr = fahr + 20) {
        printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
    }
}

/*
$ gcc chapter1/1.3/exercise_1-5/main.c -o chapter1/1.3/exercise_1-5/result.out

$ chapter1/1.3/exercise_1-5/result.out
300  148.9
280  137.8
260  126.7
240  115.6
220  104.4
200   93.3
180   82.2
160   71.1
140   60.0
120   48.9
100   37.8
 80   26.7
 60   15.6
 40    4.4
 20   -6.7
  0  -17.8
*/