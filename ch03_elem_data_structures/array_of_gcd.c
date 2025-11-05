#include <stdio.h>
#include <stdlib.h>

#define N 30

int gcd(int u, int v)
{
    if (u < 0) u = -u;
    if (v < 0) v = -v;

    while (v != 0) {
        int tmp = u % v;
        u = v;
        v = tmp;
    }

    return u;
}

int main(void) 
{
    int **arr = malloc(sizeof *arr * N);
    if (!arr) {      
        perror("malloc failed for arr");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < N; i++) {
        arr[i] = malloc(sizeof *arr[i] * N);
        if (!arr[i]) {      
            perror("malloc failed for arr[i]");
            for (int j = 0; j < i; j++)
                free(arr[j]);
            free(arr);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            arr[i][j] = (gcd(i, j) == 1);
        }
    }
    printf("     ");
    for (int i = 0; i < N; i++)
        printf("%2d ", i);
    printf("\n");
    for (int i = 0; i < N; i++) {
        printf("%2d | ", i);
        for (int j = 0; j < N; j++) {
            printf("%2d ", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < N; i++)
        free(arr[i]);
    free(arr);
    
    return 0;
}