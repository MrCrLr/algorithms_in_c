#include <stdio.h>
#include <stdlib.h>
/*--------------------------------------------------------------------------*/
// MIT 6.006 Introduction to Algorithms, Spring 2020
// Instructor: Erik Demaine
// Binary Trees, Part 1         https://www.youtube.com/watch?v=76dhtgZt38A
// Binary Trees, Part 2: AVL    https://www.youtube.com/watch?v=U1JYwHcFfso
/*--------------------------------------------------------------------------*/

typedef struct node {
    int key;
    struct node *parent;
    struct node *left;
    struct node *right;
    int height;
} node;

int height(node *n) {
    return n ? n->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int balance_factor(node *n) {
    return n ? height(n->right) - height(n->left) : 0;
}

/* ---------------- ROTATIONS ---------------- */

node *rotate_right(node *y) {
    node *x = y->left;
    node *B = x->right;

    // rotate
    x->right = y;
    y->left = B;

    // update parents
    if (B)
        B->parent = y;

    x->parent = y->parent;
    y->parent = x;

    // if y had a parent, reattach x properly
    if (x->parent) {
        if (x->parent->left == y)
            x->parent->left = x;
        else
            x->parent->right = x;
    }

    // update heights
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

node *rotate_left(node *x) {
    node *y = x->right;
    node *B = y->left;

    // rotate
    y->left = x;
    x->right = B;

    // update parents
    if (B)
        B->parent = x;

    y->parent = x->parent;
    x->parent = y;

    if (y->parent) {
        if (y->parent->left == x)
            y->parent->left = y;
        else
            y->parent->right = y;
    }

    // update heights
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

/* ---------------- REBALANCE ---------------- */

node *rebalance(node *n) {
    int bf = balance_factor(n);

    if (bf < -1) { // left-heavy
        if (balance_factor(n->left) > 0)
            n->left = rotate_left(n->left); // fix LR case
        return rotate_right(n);
    } 
    else if (bf > 1) { // right-heavy
        if (balance_factor(n->right) < 0)
            n->right = rotate_right(n->right); // fix RL case
        return rotate_left(n);
    }

    return n; // already balanced
}

/* ---------------- INSERT ---------------- */

node *insert(node *root, int key) {
    if (!root) {
        node *n = malloc(sizeof(node));
        n->key = key;
        n->left = n->right = n->parent = NULL;
        n->height = 1;
        return n;
    }

    if (key < root->key) {
        node *child = insert(root->left, key);
        root->left = child;
        child->parent = root;
    } 
    else if (key > root->key) {
        node *child = insert(root->right, key);
        root->right = child;
        child->parent = root;
    } 
    else {
        return root; // duplicate
    }

    root->height = 1 + max(height(root->left), height(root->right));
    node *balanced = rebalance(root);

    // fix parent link if root rotated
    if (balanced->parent == NULL)
        return balanced;

    return balanced;
}

/* ---------------- SEARCH & TRAVERSAL ---------------- */

node *find(node *root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key)
        return find(root->left, key);
    else
        return find(root->right, key);
}

void inorder(node *n) {
    if (!n) return;
    inorder(n->left);
    printf("%d ", n->key);
    inorder(n->right);
}

void preorder(node *n) {
    if (!n) return;
    printf("%d ", n->key);
    preorder(n->left);
    preorder(n->right);
}

void postorder(node *n) {
    if (!n) return;
    postorder(n->left);
    postorder(n->right);
    printf("%d ", n->key);
}

/* -------------------- OUTPUT --------------------- */

void print_tree(node *root, int depth) {
    if (!root) return;

    // print right subtree first (so it appears on top)
    print_tree(root->right, depth + 1);

    // indent based on depth
    for (int i = 0; i < depth; i++)
        printf("    ");

    // print key and balance info
    int bf = balance_factor(root);
    printf("%d(h=%d,bf=%d)\n", root->key, root->height, bf);

    // then print left subtree
    print_tree(root->left, depth + 1);
}

void print_after_insert(node *root, int key) {
    printf("\nAfter inserting %d:\n", key);
    print_tree(root, 0);
    printf("----------------------\n");
}

/* ---------------- TEST MAIN ---------------- */

int main(void) {
    node *root = NULL;
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int i = 0; i < 6; i++) {
        root = insert(root, keys[i]);
        print_after_insert(root, keys[i]);  // visualize after each step
    }

    printf("Inorder:\n");
    inorder(root);
    printf("\n");

    printf("Preorder:\n");
    preorder(root);
    printf("\n");
    
    printf("Postorder:\n");
    postorder(root);
    printf("\n");
    printf("Root key: %d\n", root->key);
}