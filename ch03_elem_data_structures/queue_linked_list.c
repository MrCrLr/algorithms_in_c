#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char key;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} Queue;

void print_queue(Queue *q);
Queue *create_queue(void);
int queue_empty(Queue *q);
void enqueue(Queue *q, char value);
char dequeue(Queue *q);
void destroy_queue(Queue *q);

int main(void) 
{
    Queue *q = create_queue();
    enqueue(q, 'S'); 
    enqueue(q, 'Y'); 
    enqueue(q, 'N');
    dequeue(q); 
    enqueue(q, 'T');
    dequeue(q); 
    dequeue(q);
    enqueue(q, 'H'); 
    enqueue(q, 'E'); 
    enqueue(q, 'S');
    dequeue(q); 
    dequeue(q); 
    dequeue(q); 
    enqueue(q, 'I'); 
    enqueue(q, 'Z');
    dequeue(q); 
    dequeue(q);
    enqueue(q, 'E');
    enqueue(q, 'R');
    dequeue(q);

    destroy_queue(q);
    free(q);

    return 0;
}

Queue *create_queue(void) {
    Queue *q = calloc(1, sizeof *q);
    if (!q) {
        perror("calloc failed in create_queue");
        exit(EXIT_FAILURE);
    }
    return q;
}

int queue_empty(Queue *q) {
    return q->head == NULL;
}

void enqueue(Queue *q, char value) {
    Node *new_node = malloc(sizeof *new_node);
    if (!new_node) {
        perror("malloc failed in enqueue");
        exit(EXIT_FAILURE);
    }
    new_node->key = value;
    new_node->next = NULL;

    if (q->tail == NULL) {
        q->tail = new_node;
        q->head = q->tail;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }
    print_queue(q);
}

char dequeue(Queue *q) {
    if (queue_empty(q)) {
        fprintf(stderr, "Queue underflow\n");
        exit(EXIT_FAILURE);
    }
    Node *front = q->head;
    char value = front->key;
    q->head = front->next;
    if (q->head == NULL)
        q->tail = NULL;
    free(front);
    print_queue(q);
    return value;
}

void destroy_queue(Queue *q) {
    if (q == NULL) return;
    Node *temp = q->head;
    while (temp) {
        Node *next = temp->next;
        free(temp);
        temp = next;
    }
    q->head = q->tail = NULL;
}

void print_queue(Queue *q) {
    Node *curr = q->head;
    // printf("Queue: ");
    while (curr) {
        printf("%c", curr->key);
        curr = curr->next;
        if (curr) printf("->");
    }
    printf("\n");
}