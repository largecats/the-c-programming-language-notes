/*
Exercise 2-1. Write a program to determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate values from standard headers and by direct computation. Harder if you compute them: determine the ranges of the various floating-point types.
*/

#include <stdio.h>
#include <limits.h>
#include <float.h>
#include <math.h>

main () {
    printf("In standard header:\n");
    printf("Signed char range: %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("Unsigned char range: %d to %d\n", 0, UCHAR_MAX);
    printf("Signed short range: %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("Unsigned short range: %d to %d\n", 0, USHRT_MAX);
    printf("Signed int range: %d to %d\n", INT_MIN, INT_MAX);
    printf("Unsigned int range: %d to %u\n", 0, UINT_MAX);
    printf("Signed long range: %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("Unsigned long range: %d to %lu\n", 0, ULONG_MAX);
    printf("Direct computation:\n");
    printf("Signed char range: %.0f to %.0f\n", -pow(2, CHAR_BIT-1), pow(2, CHAR_BIT-1)-1);
    printf("Unsigned char range: %d to %.0f\n", 0, pow(2, CHAR_BIT)-1);
    printf("Signed short range: %.0f to %.0f\n", -pow(2, 16-1), pow(2, 16-1)-1);
    printf("Unsigned short range: %d to %.0f\n", 0, pow(2, 16)-1);
    printf("Signed int range: %.0f to %.0f\n", -pow(2, 32-1), pow(2, 32-1)-1);
    printf("Unsigned int range: %d to %.0f\n", 0, pow(2, 32)-1);
    printf("Signed long range: %.0f to %ld\n", -pow(2, 64-1), ~(1L<<63));
    /* 
    Maximum signed long is 2^(63)-1, but 2^63 is greater than the maximum signed int 2^63-1, so we need to
    obtain this number using bitwise operations.
    2^63-1 in binary is the signed 64 bit 0111 1111 1111 ... 1111, where the leftmost 0 denotes positive sign
    To get this binary number, we 
        1) shift 1 to the left 63 times to get 1000 0000 0000 ... 0000
        2) take complement to get 0111 1111 1111 ... 1111
    */
    printf("Unsigned long range: %d to %lu\n", 0, ~(0LU<<63)); // must use %u, otherwise will become -1 (already exceeded maximum signed long)
    /*
    Maximum signed long is 2^64-1, but again, 2^64 is greater than the maximum signed int 2^64-1, so we need
    bitwise operations.
    2^64-1 in binary is the unsigned 64 bit 1111 1111 1111 ... 1111
    To get this binary number, we
        1) shift 0 to the left 64 times to get 0000 0000 0000 ... 0000
        2) take complement to get 1111 1111 1111 ... 1111
    */
}

/*
In standard header:
Signed char range: -128 to 127
Unsigned char range: 0 to 255
Signed short range: -32768 to 32767
Unsigned short range: 0 to 65535
Signed int range: -2147483648 to 2147483647
Unsigned int range: 0 to 4294967295
Signed long range: -9223372036854775808 to 9223372036854775807
Unsigned long range: 0 to 18446744073709551615
Direct computation:
Signed char range: -128 to 127
Unsigned char range: 0 to 255
Signed short range: -32768 to 32767
Unsigned short range: 0 to 65535
Signed int range: -2147483648 to 2147483647
Unsigned int range: 0 to 4294967295
Signed long range: -9223372036854775808 to 9223372036854775807
Unsigned long range: 0 to 18446744073709551615
*/