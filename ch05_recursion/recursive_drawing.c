#include <stdio.h>
#include <stdlib.h>

void mark(char *screen, int left, int right, int segments) {
    int mid = (left + right) / 2;

    if (segments > 0) {
        screen[mid] = '|';
        mark(screen, left, mid, segments - 1);
        mark(screen, mid, right, segments - 1);
    }
}

int main(void) 
{
    int length = 144;
    int segments = 3;

    char *screen = malloc(sizeof screen  * length);
    for (int i = 0; i < length; i++)
        screen[i] = '-';

    screen[0] = '|';
    screen[length - 1] = '|';

    mark(screen, 0, length, segments);
    
    printf("\n");
    for (int i = 0; i < length; i++)
        printf("%c", screen[i]);

    printf("\n");
    printf("\n");

    free(screen);

    return 0;
}