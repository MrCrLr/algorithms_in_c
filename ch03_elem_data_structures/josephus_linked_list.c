#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *next;
} Node;

int main(void) {
    int i, N, M;
    Node *tail, *head;
    
    scanf("%d %d", &N, &M);
    
    tail = malloc(sizeof *tail);
    tail->key = 1;
    head = tail;

    for (i = 2; i <= N; i++) {
        tail->next = malloc(sizeof *tail);
        tail = tail->next;
        tail->key = i;
    }
    tail->next = head;
    while (tail != tail->next) {
        for (i = 1; i < M; i++) {
            tail = tail->next;
        }
        printf("%d ", tail->next->key);
        head = tail->next;
        tail->next = tail->next->next;
        free(head);
    }
    printf("%d\n", tail->key);
}