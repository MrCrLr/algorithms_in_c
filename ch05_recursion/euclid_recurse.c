// Chapter 5, exercise 10:
#include <stdio.h>
#include <string.h>

int gcd(int u, int v) {
    if (u < 0) u = -u;
    if (v < 0) v = -v;
    
    if (v == 0) return u;
    
    return gcd(v, u % v);
}

int main(void) 
{
    int x, y;
    printf("Enter two positive integers (Ctrl+D to exit):\n");
    
    while (scanf("%d %d", &x, &y) != EOF) {
        if (x == 0 && y == 0) {
            printf("Both zero - GCD undefined.\n\n");
            continue;
        }

        int g = gcd(x, y);
        printf("x = %d, y = %d, gcd = %d\n", x, y, g);
        printf("Simplified fraction = %d/%d\n\n", x / g, y / g);
        printf("Enter next pair (Ctrl+D to exit):\n");
    }
    printf("\nGoodbye!\n");    

    return 0;
}