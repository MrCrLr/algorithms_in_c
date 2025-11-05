#include <stdio.h>
#include <stdlib.h>

typedef enum { 
    PREORDER = 1, 
    INORDER = 2, 
    POSTORDER = 3
} trav;

typedef struct {
    int left;
    int right;
    int level;
    int gen;
} state;

void mark(char **screen, state s, trav traversal, int *counter) 
{
    if (s.gen == 0) return;
    int mid = (s.left + s.right) / 2;

    state left_child  = { s.left, mid - 1, s.level + 2, s.gen - 1 };
    state right_child = { mid + 1, s.right, s.level + 2, s.gen - 1 };

    if (traversal == PREORDER) {
        char curr = (*counter < 26) ? 'A' + *counter : 'a' + (*counter - 26) % 26;
        (*counter)++;
        screen[s.level][mid] = curr;
    }

    mark(screen, left_child, traversal, counter);

    if (traversal == INORDER){
        char curr = (*counter < 26) ? 'A' + *counter : 'a' + (*counter - 26) % 26;
        (*counter)++;
        screen[s.level][mid] = curr;
    }
    
    mark(screen, right_child, traversal, counter);

    if (traversal == POSTORDER) {
        char curr = (*counter < 26) ? 'A' + *counter : 'a' + (*counter - 26) % 26;
        (*counter)++;
        screen[s.level][mid] = curr;
    }
}

int main(void) 
{

    int generations;
    trav traversal;

    printf("Number of generations in binary tree (btw 1-6): ");
    if (scanf("%d", &generations) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    printf("\nChoose traversal order:\n");
    printf("1. Preorder\n");
    printf("2. Inorder\n");
    printf("3. Postorder\n");

    if (scanf("%d", &traversal) != 1) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    int width = generations * 2 * 10;
    int height = generations * 2 + 3;

    char **screen = malloc(height * sizeof *screen);
    if (!screen) exit(EXIT_FAILURE);

    for (int j = 0; j < height; j++) {
        screen[j] = malloc(width * sizeof *screen[j]);
        if (!screen[j]) exit(EXIT_FAILURE);
    }

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            if (i == width - 1 || i == 0)
                screen[j][i] = '|';
            else if (j == height - 1 || j == 0)
                screen[j][i] = '-';
            else
                screen[j][i] = ' ';
        }
    }
    int counter = 0;
    state root = { 2, width - 2, 2, generations };
    mark(screen, root, traversal, &counter);
    
    printf("\n");
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
        printf("%c", screen[j][i]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");

    for (int j = 0; j < height; j++)
        free(screen[j]);
    free(screen);
    
    return 0;
}