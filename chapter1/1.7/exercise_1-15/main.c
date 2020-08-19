/*
Exercise 1.15. Rewrite the temperature conversion program of Section 1.2 to use a function for conversion
*/

#include <stdio.h>

float convert(int fahr) {
    return (5.0/9.0) * (fahr - 32);
}

int main()
{
    printf("%3s %6s\n", "fahr", "celsius");
    for (int fahr = 0; fahr <= 300; fahr = fahr + 20) {
        printf("%3d %6.1f\n", fahr, convert(fahr));
    }
    return 0;
}

/*
$ gcc chapter1/1.7/exercise_1-15/main.c -o chapter1/1.7/exercise_1-15/result.out

$ chapter1/1.7/exercise_1-15/result.out
fahr celsius
  0  -17.8
 20   -6.7
 40    4.4
 60   15.6
 80   26.7
100   37.8
120   48.9
140   60.0
160   71.1
180   82.2
200   93.3
220  104.4
240  115.6
260  126.7
280  137.8
300  148.9
*/