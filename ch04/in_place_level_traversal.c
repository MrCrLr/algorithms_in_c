
typedef struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
} Node;
 

Node* connect(Node* root) {
    if (!root) return NULL;
    
    Node *curr = root;
    
    while (curr) {
        Node dummy = {0, NULL, NULL, NULL};
        Node *tail = &dummy;

        while (curr) {
            if (curr->left) {
                tail->next = curr->left;
                tail = tail->next;
            }
            if (curr->right) {
                tail->next = curr->right;
                tail = tail->next;
            }
            curr = curr->next;
        }
        curr = dummy.next;
    }
    return root;
}