#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node *left;   // first child
    struct Node *right;  // next sibling
} tree_node_t;

typedef struct qnode {
    tree_node_t *data;
    struct qnode *next;
} qnode_t;

typedef struct {
    qnode_t *head;
    qnode_t *tail;
} queue_t;

void print_queue(queue_t *q);
queue_t *create_queue(void);
int queue_empty(queue_t *q);
void enqueue(queue_t *q, tree_node_t *node);
tree_node_t *dequeue(queue_t *q);
void destroy_queue(queue_t *q);
void traverse_level_order(tree_node_t *root);

int main(void) 
{
    tree_node_t *F = malloc(sizeof *F);
    tree_node_t *I = malloc(sizeof *I);
    tree_node_t *R = malloc(sizeof *R);
    tree_node_t *E = malloc(sizeof *E);

    F->data = 'F';  F->left = I;     F->right = NULL;
    I->data = 'I';  I->left = R;  I->right = NULL;
    R->data = 'R';  R->left = NULL;  R->right = E;
    E->data = 'E';  E->left = NULL;  E->right = NULL;

    
    tree_node_t *forest_root = F;

    printf("Level-order traversal: ");
    traverse_level_order(forest_root);
    printf("\n");

    free(E);
    free(R);
    free(I);
    free(F);

    return 0;
}

void traverse_level_order(tree_node_t *root) {
    if (!root) return;
    queue_t *q = create_queue();
    enqueue(q, root);

    while (!queue_empty(q)) {
        tree_node_t *node = dequeue(q);
        printf("%c ", node->data);

        tree_node_t *child = node->left;
        while (child) {
            enqueue(q, child);
            child = child->right;
        }
    }
    destroy_queue(q);
}

queue_t *create_queue(void) {
    queue_t *q = calloc(1, sizeof *q);
    if (!q) {
        perror("calloc failed in create_queue");
        exit(EXIT_FAILURE);
    }
    return q;
}

int queue_empty(queue_t *q) {
    return q->head == NULL;
}

void enqueue(queue_t *q, tree_node_t *node) {
    qnode_t *new_node = malloc(sizeof *new_node);
    if (!new_node) {
        perror("malloc failed in enqueue");
        exit(EXIT_FAILURE);
    }
    new_node->data = node;
    new_node->next = NULL;

    if (q->tail == NULL) {
        q->tail = new_node;
        q->head = q->tail;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
    //print_queue(q);
}

tree_node_t *dequeue(queue_t *q) {
    if (queue_empty(q)) {
        fprintf(stderr, "Queue underflow\n");
        exit(EXIT_FAILURE);
    }
    qnode_t *front = q->head;
    tree_node_t *result = front->data;
    q->head = front->next;
    if (q->head == NULL)
        q->tail = NULL;
    free(front);
    //print_queue(q);
    return result;
}

void destroy_queue(queue_t *q) {
    if (q == NULL) return;
    qnode_t *temp = q->head;
    while (temp) {
        qnode_t *next = temp->next;
        free(temp);
        temp = next;
    }
    q->head = q->tail = NULL;
}

void print_queue(queue_t *q) {
    qnode_t *curr = q->head;
    // printf("Queue: ");
    while (curr) {
        tree_node_t *node = curr->data;
        printf("%c", node->data);
        curr = curr->next;
        if (curr) printf("->");
    }
    printf("\n");
}