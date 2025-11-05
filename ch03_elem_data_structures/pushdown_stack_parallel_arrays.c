#include <stdio.h>
#include <stdlib.h>

#define MAX 10
int key[MAX];
int next[MAX];
int top, freep;

void init_stack(void) {
    top = 0;
    for (int i = 1; i < MAX - 1; i++)
        next[i] = i + 1;
    next[MAX - 1] = 0;
    freep = 1;
}

void push(int val) {
    int i = freep;
    freep = next[i];
    key[i] = val;
    next[i] = top;
    top = i;
}

int pop(void) {
    if (top == 0) {
        printf("Stack underflow!\n");
        return -1;
    }
    int i = top;
    int val = key[i];
    top = next[i];
    next[i] = freep;
    freep = i;
    return val;
}

int main(void) 
{
    init_stack();
    push(10);
    push(20);
    push(30);

    printf("%d\n", pop()); // 30
    printf("%d\n", pop()); // 20
    printf("%d\n", pop()); // 10

    return 0;
}