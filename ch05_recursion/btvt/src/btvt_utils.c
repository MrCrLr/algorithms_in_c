#include "btvt_utils.h"

// Convert pixel from 2d (0,0 bottom left) to 1d
static inline pixel *pixel_at(image_t *img, int x, int y) {
    return &img->data[y * img->w + x];
}

void set_pixel(image_t *img, int x, int y, pixel color)
{
    if (x < 0 || x >= img->w || y < 0 || y >= img->h) 
        return;
    pixel *p = pixel_at(img, x, y);
    *p = color;
}

void draw_line(image_t *img, int x0, int y0, int x1, int y1, pixel color)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        set_pixel(img, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void draw_circle(image_t *img, int cx, int cy, int radius, pixel color, int fill)
{
    int x = radius, y = 0;
    int err = 0;

    while (x >= y) {
        if (fill) {
            // draw horizontal lines to fill
            for (int i = cx - x; i <= cx + x; i++) {
                set_pixel(img, i, cy + y, color);
                set_pixel(img, i, cy - y, color);
            }
            for (int i = cx - y; i <= cx + y; i++) {
                set_pixel(img, i, cy + x, color);
                set_pixel(img, i, cy - x, color);
            }
        } else {
            // outline only
            set_pixel(img, cx + x, cy + y, color);
            set_pixel(img, cx + y, cy + x, color);
            set_pixel(img, cx - y, cy + x, color);
            set_pixel(img, cx - x, cy + y, color);
            set_pixel(img, cx - x, cy - y, color);
            set_pixel(img, cx - y, cy - x, color);
            set_pixel(img, cx + y, cy - x, color);
            set_pixel(img, cx + x, cy - y, color);
        }

        y += 1;
        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x -= 1;
            err += 2 * (y - x) + 1;
        }
    }
}

void draw_char(image_t *img, int x, int y, char c, pixel color)
{
    for (int row = 0; row < 8; row++) {
        uint8_t bits = font8x8_basic[(uint8_t)c][row];
        for (int col = 0; col < 8; col++) {
            if (bits & (1 << col))
                set_pixel(img, x + col, y + row, color);
        }
    }
}

void draw_char_scaled(image_t *img, int x, int y, char c, pixel color, int scale)
{
    if (c < 0 || c > 127) return; // protect bounds

    for (int row = 0; row < 8; row++) {
        uint8_t bits = font8x8_basic[(uint8_t)c][row];

        for (int col = 0; col < 8; col++) {
            if (bits & (1 << col)) {
                // scale each pixel into a scale×scale block
                for (int dy = 0; dy < scale; dy++) {
                    for (int dx = 0; dx < scale; dx++) {
                        set_pixel(img, x + col * scale + dx,
                                  y + row * scale + dy, color);
                    }
                }
            }
        }
    }
}

void draw_string_scaled(image_t *img, int x, int y,
                        const char *text, pixel color, int scale)
{
    if (!text) return;

    int cursor_x = x;
    int cursor_y = y;
    const int char_width = 8 * scale;

    for (const char *p = text; *p; p++) {
        if (*p == '\n') {
            cursor_x = x;
            cursor_y += 8 * scale + 2; // newline → move down one line
            continue;
        }

        draw_char_scaled(img, cursor_x, cursor_y, *p, color, scale);
        cursor_x += char_width; // advance cursor
    }
}

void draw_paragraph_scaled(image_t *img, int x, int y,
                           const char *text, pixel color, int scale)
{
    int max_chars_per_line = (img->w - x * 2) / (8 * scale);

    int line_count = 0;
    char **lines = split_lines(text, max_chars_per_line, &line_count);

    for (int i = 0; i < line_count; i++) {
        int y_offset = y + i * (8 * scale * 5 / 3);
        draw_string_scaled(img, x, y_offset, lines[i], color, scale);
        free(lines[i]);
    }
    free(lines);
}

char **split_lines(const char *text, int max_chars_per_line, int *out_line_count) {
    int len = strlen(text);
    int capacity = (len / max_chars_per_line) + 2; // rough upper bound
    char **lines = calloc(capacity, sizeof *lines);
    if (!lines) return NULL;

    int start = 0;
    int line = 0;
    while (start < len) {
        int remaining = len - start;
        int chunk = remaining < max_chars_per_line ? remaining : max_chars_per_line;

        // try to break on space before max width
        int end = start + chunk;
        while (end > start && end < len && text[end] != ' ' && text[end] != '\n')
            end--;

        if (end == start) end = start + chunk; // no space found, hard break

        int copy_len = end - start;
        lines[line] = calloc(copy_len + 1, 1);
        memcpy(lines[line], &text[start], copy_len);
        lines[line][copy_len] = '\0';

        // skip spaces/newlines for next line
        while (text[end] == ' ' || text[end] == '\n') end++;
        start = end;
        line++;
    }

    *out_line_count = line;
    return lines;
}
