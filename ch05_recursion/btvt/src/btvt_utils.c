#include "btvt_utils.h"

// Convert pixel from 2d (0,0 bottom left) to 1d
static inline pixel *pixel_at(pixel *img, int w, int x, int y) {
    return &img[y * w + x];
}

void set_pixel(pixel *img, int w, int h, int x, int y,
               unsigned char r, unsigned char g, unsigned char b)
{
    if (x < 0 || x >= w || y < 0 || y >= h) 
        return;
    pixel *p = pixel_at(img, w, x, y);
    p->r = r;
    p->g = g;
    p->b = b;
}

void draw_line(pixel *img, int w, int h,
               int x0, int y0, int x1, int y1,
               unsigned char r, unsigned char g, unsigned char b)
{
    int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
    int err = dx + dy, e2;

    while (1) {
        set_pixel(img, w, h, x0, y0, r, g, b);
        if (x0 == x1 && y0 == y1) break;
        e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void draw_circle(pixel *img, int w, int h,
                 int cx, int cy, int radius,
                 unsigned char r, unsigned char g, unsigned char b,
                 int fill)
{
    int x = radius, y = 0;
    int err = 0;

    while (x >= y) {
        if (fill) {
            // draw horizontal lines to fill
            for (int i = cx - x; i <= cx + x; i++) {
                set_pixel(img, w, h, i, cy + y, r, g, b);
                set_pixel(img, w, h, i, cy - y, r, g, b);
            }
            for (int i = cx - y; i <= cx + y; i++) {
                set_pixel(img, w, h, i, cy + x, r, g, b);
                set_pixel(img, w, h, i, cy - x, r, g, b);
            }
        } else {
            // outline only
            set_pixel(img, w, h, cx + x, cy + y, r, g, b);
            set_pixel(img, w, h, cx + y, cy + x, r, g, b);
            set_pixel(img, w, h, cx - y, cy + x, r, g, b);
            set_pixel(img, w, h, cx - x, cy + y, r, g, b);
            set_pixel(img, w, h, cx - x, cy - y, r, g, b);
            set_pixel(img, w, h, cx - y, cy - x, r, g, b);
            set_pixel(img, w, h, cx + y, cy - x, r, g, b);
            set_pixel(img, w, h, cx + x, cy - y, r, g, b);
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

void draw_char(pixel *img, int w, int h,
               int x, int y, char c,
               unsigned char r, unsigned char g, unsigned char b)
{
    for (int row = 0; row < 8; row++) {
        unsigned char bits = font8x8_basic[(int)c][row];
        for (int col = 0; col < 8; col++) {
            if (bits & (1 << col))
                set_pixel(img, w, h, x + col, y + row, r, g, b);
        }
    }
}

void draw_char_scaled(pixel *img, int w, int h,
                      int x, int y, char c,
                      unsigned char r, unsigned char g, unsigned char b,
                      int scale)
{
    if (c < 0 || c > 127) return; // protect bounds

    for (int row = 0; row < 8; row++) {
        unsigned char bits = font8x8_basic[(int)c][row];

        for (int col = 0; col < 8; col++) {
            if (bits & (1 << col)) {
                // scale each pixel into a scale×scale block
                for (int dy = 0; dy < scale; dy++) {
                    for (int dx = 0; dx < scale; dx++) {
                        set_pixel(img, w, h,
                                  x + col * scale + dx,
                                  y + row * scale + dy,
                                  r, g, b);
                    }
                }
            }
        }
    }
}
