#include <stdio.h>
#include <string.h>

int gcd(int u, int v, int verbose)
{
    if (u < 0) u = -u;
    if (v < 0) v = -v;

    if (verbose)
        printf("Starting GCD with u=%d, v=%d\n", u, v);

    while (v != 0) {
        int tmp = u % v;
        if (verbose)
            printf("u=%d, v=%d, tmp=%d\n", u, v, tmp);
        u = v;
        v = tmp;
    }

    if (verbose)
        printf("Final gcd = %d\n\n", u);

    return u;
}

int main(int argc, char *argv[]) 
{
    int verbose = 0;
    if (argc > 1 && strcmp(argv[1], "-v") == 0) 
            verbose = 1;

    int x, y;
    printf("Enter two positive integers (Ctrl+D to exit):\n");
    
    while (scanf("%d %d", &x, &y) != EOF) {
        if (x == 0 && y == 0) {
            printf("Both zero - GCD undefined.\n\n");
            continue;
        }
        
        int g = gcd(x, y, verbose);
        printf("x = %d, y = %d, gcd = %d\n", x, y, g);
        printf("Simplified fraction = %d/%d\n\n", x / g, y / g);
        printf("Enter next pair (Ctrl+D to exit):\n");
    }
    printf("\nGoodbye!\n");    
    return 0;
}