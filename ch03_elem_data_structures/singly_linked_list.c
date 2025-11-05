#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *next;
} Node;

// Initialize linked list with sentinel nodes at head and tail
Node *init_list() {
    Node *head = malloc(sizeof *head);
        if (!head) {
        perror("malloc failed for head in init_list");
        exit(EXIT_FAILURE);
    }
    Node *tail = malloc(sizeof *tail);
        if (!tail) {
        perror("malloc failed for x in init_list");
        exit(EXIT_FAILURE);
    }
    head->next = tail;
    tail->next = tail; 
    return head;
}

void delete_next(Node *curr) {
    if (curr == NULL || curr->next == NULL) {
        return;
    }
    Node *target = curr->next;
    curr->next = target->next;
    free(target);
}

Node *insert_after(int value, Node *curr) {
    Node *new_node = malloc(sizeof *new_node);
    if (!new_node) {
        perror("malloc failed in insert_after");
        exit(EXIT_FAILURE);
    }
    new_node->key = value;
    new_node->next = curr->next;
    curr->next = new_node;
    return new_node;
}

Node *move_next_to_front(Node *head, Node *tail, Node *curr) {
    if (!head || !curr || !curr->next) return head;
    if (curr->next == tail) return head;

    Node *target = curr->next;
    curr->next = target->next;
    target->next = head->next;
    head->next = target;

    return head;
}

Node *exchange(Node *head, Node *tail, Node *left, Node *right) {
    if (!head || !left || !left->next || !right || !right->next) return head;
    if (left->next == tail || right->next == tail) return head;
    if (left == right) return head;

    Node *x = left->next;
    Node *y = right->next;

    // Case 1: Non-adjacent
    if (x != right && y != left) {
        Node *tmp = x->next;
        left->next = y;
        right->next = x;
        x->next = y->next;
        y->next = tmp;
        return head;
    }
    // Case 2: Adjacent (x follows left, and y == x->next)
    // left -> x -> y
    if (right == x) {
        left->next = y;
        x->next = y->next;
        y->next = x;
        return head;
    }
    // Case 3: Adjacent reversed (right before left)
    if (left == y) {
        right->next = x;
        y->next = x->next;
        x->next = y;
        return head;
    }

    return head;
}

void print_list(Node *head) {
    Node *tmp = head->next;
    while (tmp->next != tmp) {
        printf("%d", tmp->key);
        tmp = tmp->next;
        if (tmp->next != tmp) printf("->");
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *target = head;
    while (target->next != target) {
        Node *next = target->next;
        free(target);
        target = next;
    }
    free(target); // free tail sentinel
}

int main(void) 
{
    Node *head = init_list();
    Node *tail = head->next;
    
    Node *t = insert_after(10, head);
    Node *u = insert_after(20, t);
    u = insert_after(30, u);
    Node *w = insert_after(40, u);
    w = insert_after(50, w);
    w = insert_after(60, w);

    printf("t->key = %d, u->key = %d, w->key = %d\n", t->key, u->key, w->key);
    print_list(head);

    move_next_to_front(head, tail, u);
    print_list(head);

    exchange(head, tail, t, u);
    print_list(head);

    delete_next(head->next->next);
    print_list(head);

    free_list(head);

    return 0;
}