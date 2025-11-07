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

char calculate_letter(int *counter) {
    static const char base64[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789#$";
    char curr = base64[(*counter) % 64];
    (*counter)++;
    return curr;
}

void build_tree(char **screen, state s, trav traversal, int *counter) 
{
    if (s.gen == 0) return;
    // find current mid point
    int mid = (s.left + s.right) / 2;

    // Set state based on current midpoint
    // Levels are always 2 line skips while width scales
    state left_child  = { s.left, mid - 1, s.level + 2, s.gen - 1 };
    state right_child = { mid + 1, s.right, s.level + 2, s.gen - 1 };

    if (traversal == PREORDER) {
        screen[s.level][mid] = calculate_letter(counter);
    }

    build_tree(screen, left_child, traversal, counter);

    if (traversal == INORDER) {
        screen[s.level][mid] = calculate_letter(counter);
    }

    build_tree(screen, right_child, traversal, counter);

    if (traversal == POSTORDER) {
        screen[s.level][mid] = calculate_letter(counter);
    }
}

int main(void) 
{
    // Get user input
    int generations;
    trav traversal;

    printf("Number of generations in binary tree (btw 1-6): ");
    if (scanf("%d", &generations) != 1 || generations < 1 || generations > 6) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    printf("\nChoose traversal order:\n");
    printf("1. Preorder\n");
    printf("2. Inorder\n");
    printf("3. Postorder\n");

    if (scanf("%d", &traversal) != 1 || traversal < 1 || traversal > 3) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    // Adjusted dimensions for aesthetics of frame.
    int width = generations * 2 * 10;
    int height = generations * 2 + 3;

    // Declare 2-d array
    char **screen = malloc(height * sizeof *screen);
    if (!screen) exit(EXIT_FAILURE);

    for (int j = 0; j < height; j++) {
        screen[j] = malloc(width * sizeof *screen[j]);
        if (!screen[j]) exit(EXIT_FAILURE);
    }

    // Initialize 2-d array and build frame
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
    // Set state for initial call to build_tree function and set counter
    int counter = 0;
    state root = { 2, width - 2, 2, generations };
    build_tree(screen, root, traversal, &counter);
    
    // Print tree and creation
    printf("\n");
    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
        printf("%c", screen[j][i]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");

    // Free memory 2-d array
    for (int j = 0; j < height; j++)
        free(screen[j]);
    free(screen);
    
    return 0;
}