#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *prev;
    struct Node *next;
} Node;

Node *list_init(int value) {
    Node *head = malloc(sizeof *head);
    if (!head) {
        perror("malloc failed in list_init");
        exit(EXIT_FAILURE);
    }
    head->key = value;
    head->prev = NULL;
    head->next = NULL;
    return head;
}

Node *insert_at_start(Node *head, int value) {
    Node *new_node = malloc(sizeof *new_node);
    if (!new_node) {
        perror("malloc failed in insert_at_start");
        exit(EXIT_FAILURE);
    }
    new_node->key = value;
    new_node->prev = NULL;
    new_node->next = head;

    if (head)
        head->prev = new_node;

    return new_node;
}

Node *find(Node *head, int value) {
    Node *target = head;
    while (target && target->key != value) {
        target = target->next;
    }
    return target;
}

void delete_node(Node **head, Node *target) {
    if (!target) 
        return;

    if (target == *head) { 
        *head = target->next;
        if (*head)
            (*head)->prev = NULL;
        free(target);
        return;
    }

    if (target->prev) 
        target->prev->next = target->next;
    if (target->next)
        target->next->prev = target->prev;

    free(target);
}

void print_list(Node *head) {
    Node *tmp = head;

    while (tmp) {
        printf("%d", tmp->key);
        tmp = tmp->next;
        if (tmp) printf("->");
    }
    printf("\n");
}

void free_list(Node *head) {
    Node *tmp = head;
    while (tmp) {
        Node *next = tmp->next;
        free(tmp);
        tmp = next;
    }
}

int main(void) 
{
    Node *head = NULL;
    for (int i = 1; i <= 10; i++) {
        head = insert_at_start(head, i);
    }
    
    printf("Initial list: ");
    print_list(head);

    int num;
    printf("What number to delete? ");
    scanf("%d", &num);

    Node *target = find(head, num);

    if (target) {
        delete_node(&head, target);
        printf("After deleting %d: ", num);
        print_list(head);
    } else {
        printf("%d not found; list unchanged.\n", num);
    }

    free_list(head);
    return 0;
}