#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
} point_t;

typedef struct {
    point_t a;
    point_t b;
} line_t;

typedef struct {
    char *img;
    int h, w;
} screen_t;

void draw_line(line_t *line, screen_t *view) {
    if (abs(line->a.x - line->b.x) <= 1 && abs(line->a.y - line->b.y) <= 1)
        return;

    point_t mid = {
        .x = (line->a.x + line->b.x) / 2,
        .y = (line->a.y + line->b.y) / 2
    };

    int mid_index = view->w * mid.y + mid.x;
    if (mid_index >= 0 && mid_index < view->w * view->h)
        view->img[mid_index] = '.';

    int start_index = view->w * line->a.y + line->a.x;
    int end_index   = view->w * line->b.y + line->b.x;
    view->img[start_index] = '.';
    view->img[end_index]   = '.';

    line_t left  = { .a = line->a, .b = mid };
    line_t right = { .a = mid,     .b = line->b };

    draw_line(&left, view);
    draw_line(&right, view);
}

void create_view(screen_t *view, int width, int height) {
    view->w = width;
    view->h = height;
    int len = view->w * view->h;

    view->img = calloc(len, sizeof view->img);
    
    for (int i = 0; i < len; i++) {
        int row = i / view->w;
        int col = i % view->w;
        if (row == 0 || row == view->h - 1) {
            view->img[i] = '-';
        } else if (col == 0 || col == view->w - 1) {
            view->img[i] = '|';
        } else {
            view->img[i] = ' ';
        }
    }
}

int main(void) 
{
    screen_t *view = malloc(sizeof *view);
    int width = 80;
    int height = 30;
    create_view(view, width, height);

    line_t line1 = { .a.x=10, .a.y=3,  .b.x=78, .b.y=25 };
    line_t line2 = { .a.x=50, .a.y=5,  .b.x=2,  .b.y=28 };
    line_t line3 = { .a.x=65, .a.y=10, .b.x=50, .b.y=22 };

    draw_line(&line1, view);
    draw_line(&line2, view);
    draw_line(&line3, view);

    // output screen
    // size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    for (int r = 0; r < view->h; r++) {
        fwrite(&view->img[r * view->w], 1, view->w, stdout);
        putchar('\n');
    }

    return 0;
}