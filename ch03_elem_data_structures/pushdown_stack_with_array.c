#include <stdio.h>
#include <stdlib.h>

#define max 100

static char stack[max+1];
static int p;

void print_stack(void) {
    for (int i = 0; i < p; i++)
        printf("%c ", stack[i]);
    printf("\n");
}

int stack_empty(void) {
    return !p;
}

void push(char c) {
    print_stack();
    stack[p++] = c;
}

char pop(void) {
    if (stack_empty()) {
        printf("Stack empty!");
        return 0;
    } else {
        print_stack();
        return stack[--p];
    }
}

void stack_init(void) {
    p = 0;
}

int main(void) 
{
    stack_init();

    push('C');
    push('Y');
    push('B');
    pop();  
    push('O');
    pop();
    pop();        
    push('R');
    push('G'); 
    pop();
    pop();
    pop();

    return 0;
}