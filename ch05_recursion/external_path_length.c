#include <stdio.h>
#include <stdlib.h>

typedef struct bt_node {
    struct bt_node *left;
    struct bt_node *right;
} bt_node_t; // Example of binary tree node

typedef struct f_node {
    struct f_node *left;  // child
    struct f_node *right; // sibling
} f_node_t; // Example of forest node

int external_path_length(bt_node_t *node, int depth) {
    if (node == NULL)
        return 0;
    if (node->left == NULL && node->right == NULL)
        return depth;
    else
        return external_path_length(node->left, depth + 1) 
             + external_path_length(node->right, depth + 1);
}

int external_path_length_LCRS(f_node_t *node, int depth) {
    if (node == NULL)
        return depth;
    else
        return external_path_length_LCRS(node->left, depth + 1)
             + external_path_length_LCRS(node->right, depth);
}

int main(void) 
{
    /*
    Code to declare and fill binary tree
    */
    bt_node_t *root = malloc(sizeof *root);
    bt_node_t *a = malloc(sizeof *a);
    bt_node_t *b = malloc(sizeof *b);
    bt_node_t *c = malloc(sizeof *c);

    root->left = a;  root->right = b;
    a->left = c;     a->right = NULL;
    b->left = NULL;  b->right = NULL;
    c->left = NULL;  c->right = NULL;

    int epl = external_path_length(root, 0);
    printf("External path length (binary tree): %d\n", epl);

    free(root); free(a); free(b); free(c);

    f_node_t *A = malloc(sizeof *A);
    f_node_t *B = malloc(sizeof *B);
    f_node_t *C = malloc(sizeof *C);
    f_node_t *D = malloc(sizeof *D);
    f_node_t *E = malloc(sizeof *E);
    f_node_t *F = malloc(sizeof *F);

    // Build LCRS representation
    A->left = B;  A->right = NULL;
    B->left = D;  B->right = C;
    C->left = NULL; C->right = NULL;
    D->left = NULL; D->right = E;
    E->left = NULL; E->right = F;
    F->left = NULL; F->right = NULL;

    epl = external_path_length_LCRS(A, 0);
    printf("External path length (LCRS tree): %d\n", epl);

    free(A); free(B); free(C); free(D); free(E); free(F);
    return 0;
}