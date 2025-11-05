// Stack-based implementation of postorder traversal of a binary tree
// Returns tree on Ch.4 p.38: 
// A C _ M L P O T _ E R E E T E
// s1 -> EOTEERET__PMLAC
// s2 -> ETEERE_TOPLM_CA

void postorder_iterative(Node *root) {
    if (!root) return;
    Stack *s1 = createStack();
    Stack *s2 = createStack();
    push(s1, root);

    while (!empty(s1)) {
        Node *node = pop(s1);
        push(s2, node);
        if (node->left)  push(s1, node->left);
        if (node->right) push(s1, node->right);
    }

    while (!empty(s2)) {
        Node *node = pop(s2);
        visit(node);
    }
}