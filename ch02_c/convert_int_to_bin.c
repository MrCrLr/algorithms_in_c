#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

int convert() {
    char c;
    int num = 0;
    int sign = 1;

    c = getchar();
    while (isspace((unsigned char)c)) { 
        c = getchar(); 
    }

    if (c == '-') {
        sign = -1;
        c = getchar();
    } else if (c == '+') {
        c = getchar();
    }

    while (isdigit((unsigned char)c)) {
        num = num * 10 + (c - '0'); 
        c = getchar();
    }

    num *= sign;
    return num;
}

void binary(int x) {
    if (x == 0) { 
        printf("Converted to binary: 0\n"); 
        return; 
    }

    int sign = 1;
    if (x < 0) { 
        sign = -1; 
        x = -x; 
    }

    int capacity = 8;
    int *bits = malloc(capacity * sizeof *bits);
        if (!bits) {
        perror("Malloc failed");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    while (x != 0) {
        if (count == capacity) {
            capacity *= 2;
            int *tmp = realloc(bits, capacity * sizeof *bits);
            if (!tmp) {
                perror("Realloc failed");
                exit(EXIT_FAILURE);
            }
            bits = tmp;
        }
        bits[count++] = x % 2;
        x /= 2;
    }

    printf("Converted to binary: ");
    if (sign < 0) { 
        putchar('-'); 
    }

    for (int i = count - 1; i >= 0; i--) {
        printf("%d", bits[i]);
    }
    printf("\n");

    free(bits);
}

int main(void) {

    printf("Enter a valid number: ");
    
    int num = convert();
    
    printf("Converted to int: %d\n", num);

    binary(num);

    return 0;
}