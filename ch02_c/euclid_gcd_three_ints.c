#include <stdio.h>

static int igcd(int a, int b) {
    if (a < 0) a = -a;
    if (b < 0) b = -b;

    while (b != 0) {
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}
int gcd_three(int u, int v, int w) {
    return igcd(igcd(u, v), w);
}

int main(void)
{
    int u, v, w;
    puts("Enter three integers (Ctrl+D to exit):\n");
    
    while (scanf("%d %d %d", &u, &v, &w) == 3) {
        if (u == 0 && v == 0 && w == 0) {
            puts("All zero - GCD undefined.\n");
            puts("Enter next triple (Ctrl+D to exit):");
            continue;
        }
        int g = gcd_three(u, v, w);
        printf("u = %d, v = %d, w = %d\n", u, v, w);
        printf("Greatest common divisor = %d\n\n", g);
        printf("Enter next pair (Ctrl+D to exit):\n");
    }
    printf("\nGoodbye!\n");    
    return 0;
}