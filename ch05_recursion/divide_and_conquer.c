// Chapter 5, exercise 8:
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
    char *buf;
    int h, w;
} canvas_t;

static inline int index_2d(const canvas_t *c, int x, int y) {
    return c->w * y + x;
}

void draw_recursive_line(const line_t *line, canvas_t *c) {
    if (abs(line->a.x - line->b.x) <= 1 && abs(line->a.y - line->b.y) <= 1)
        return;

    point_t mid = {
        .x = (line->a.x + line->b.x) / 2,
        .y = (line->a.y + line->b.y) / 2
    };

    if (mid.x >= 0 && mid.x < c->w && mid.y >= 0 && mid.y < c->h) {
        int idx = index_2d(c, mid.x, mid.y);
        c->buf[idx] = '.';
    }

    line_t left  = { .a = line->a, .b = mid };
    line_t right = { .a = mid,     .b = line->b };

    draw_recursive_line(&left, c);
    draw_recursive_line(&right, c);
}

void init_canvas(canvas_t *c, int width, int height) {
    c->w = width;
    c->h = height;
    int num_cells = c->w * c->h;

    c->buf = calloc(num_cells, sizeof *c->buf);
        if (!c->buf) {
            perror("calloc c->buf failed in init_canvas");
            exit(EXIT_FAILURE);
        }
    
    for (int i = 0; i < num_cells; i++) {
        int row = i / c->w;
        int col = i % c->w;
        if (row == 0 || row == c->h - 1) {
            c->buf[i] = '-';
        } else if (col == 0 || col == c->w - 1) {
            c->buf[i] = '|';
        } else {
            c->buf[i] = ' ';
        }
    }
}

void print_canvas(canvas_t *c) {
    for (int r = 0; r < c->h; r++) {
        // size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);    
        fwrite(&c->buf[r * c->w], 1, c->w, stdout);
        putchar('\n');
    }
}

int main(void) 
{
    canvas_t canvas;
    int width = 80;
    int height = 30;
    init_canvas(&canvas, width, height);

    const line_t line1 = { .a.x=10, .a.y=3,  .b.x=78, .b.y=25 };
    const line_t line2 = { .a.x=50, .a.y=5,  .b.x=2,  .b.y=28 };
    const line_t line3 = { .a.x=65, .a.y=10, .b.x=50, .b.y=22 };

    draw_recursive_line(&line1, &canvas);
    draw_recursive_line(&line2, &canvas);
    draw_recursive_line(&line3, &canvas);

    print_canvas(&canvas);
    free(canvas.buf);

    return 0;
}