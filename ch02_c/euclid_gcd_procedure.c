#include <stdio.h>

typedef struct {
    unsigned long long numerator;
    unsigned long long denominator;
} Fraction;

void gcd(Fraction *f) {
    unsigned long long u = f->numerator;
    unsigned long long v = f->denominator;

    if (u < 0) u = -u;
    if (v < 0) v = -v;

    while (v != 0) {
        unsigned long long tmp = u % v;
        u = v;
        v = tmp;
    }
    
    if (f->denominator < 0) u = -u;

    f->numerator /= u;
    f->denominator /= u;
}

int main(void) 
{
    unsigned long long x, y;
    printf("Enter two positive integers (Ctrl+D to exit):\n");
    
    while (scanf("%llu %llu", &x, &y) != EOF) {
        if (x == 0 && y == 0) {
            printf("Both zero - GCD undefined.\n\n");
            continue;
        }
        Fraction f = { .numerator=x, .denominator=y };
        gcd(&f);
        printf("x = %llu, y = %llu\n", x, y);
        printf("Simplified fraction = %llu/%llu\n\n", f.numerator, f.denominator);
        printf("Enter next pair (Ctrl+D to exit):\n");
    }
    printf("\nGoodbye!\n");    
    return 0;
}

// Largest pair of representable numbers in my system
// whose greatest common divisor is 1:
/* 
$ ./euclid_gcd_procedure
Enter two positive integers (Ctrl+D to exit):
Enter next pair (Ctrl+D to exit):
18446744073709551614 18446744073709551615
x = 18446744073709551614, y = 18446744073709551615
Simplified fraction = 18446744073709551614/18446744073709551615
*/