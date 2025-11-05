#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    char info;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct stack_node {
    void *data;
    struct stack_node *next;
} stack_node_t;

void push(stack_node_t **top, void *data) {
    stack_node_t *new_node = malloc(sizeof *new_node);
    if (!new_node) {
        perror("malloc failed in push()");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

void *pop(stack_node_t **top) {
    if (*top == NULL) {
        fprintf(stderr, "Error: pop() on empty stack\n");
        exit(EXIT_FAILURE);
    }
    stack_node_t *temp = *top;
    void *data = temp->data;
    *top = temp->next;
    free(temp);
    return data;
}

void free_stack(stack_node_t *top) {
    stack_node_t *tmp = top;
    while (tmp) {
        stack_node_t *next = tmp->next;
        free(tmp);
        tmp = next;
    }
}

void print_stack(stack_node_t *top) {
    printf("stack top -> ");
    for (stack_node_t *curr = top; curr; curr = curr->next) {
        tree_node_t *node = curr->data;
        printf("[%c] ", node->info);
    }
    printf("\n");
}

void free_tree(tree_node_t *x, tree_node_t *z) {
    if (x == z) return;
    free_tree(x->left, z);
    free_tree(x->right, z);
    free(x);
}

void print_tree(tree_node_t *node, tree_node_t *z) {
    if (node == z) return;
    print_tree(node->left, z);
    printf("%c ", node->info);
    print_tree(node->right, z);
}

int main(void) 
{
    tree_node_t *x, *z;
    char c;
    stack_node_t *stack = NULL;

    z = malloc(sizeof *z);
    if (!z) {
        perror("malloc failed for sentinel z");
        exit(EXIT_FAILURE);
    }
    z->info = '#'; // sentinel marker
    z->left = z->right = z;

    // Takes user input: e.g., ABC+DE**F+* 
    printf("Enter postfix question: ");
    while (scanf(" %c", &c) == 1 && c != '\n') {
        x = malloc(sizeof *x);
        if (!x) {
            perror("malloc failed for tree node");
            exit(EXIT_FAILURE);
        }
        *x = (tree_node_t){ .info = c, .left = z, .right = z };
        
        printf("Read: %c\n", c);

        if (c=='+' || c == '*') {
            x->right = pop(&stack); 
            x->left = pop(&stack);
        }
        push(&stack, x);
        print_stack(stack);
    }
    tree_node_t *root = pop(&stack);
    
    printf("Root node info: %c\n", root->info);
    print_tree(root, z);
    printf("\n");

    free_stack(stack);
    free_tree(root, z);
    free(z);

    return 0;
}