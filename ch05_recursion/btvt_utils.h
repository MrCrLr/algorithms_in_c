#ifndef BTVT_UTILS_H
#define BTVT_UTILS_H

#include "btvt_types.h"
#include "btvt_fonts.h"

static inline pixel *pixel_at(pixel *img, int w, int h, int x, int y);

void set_pixel(pixel *img, int w, int h, int x, int y, 
               unsigned char r, unsigned char g, unsigned char b);

void draw_line(pixel *img, int w, int h,
               int x0, int y0, int x1, int y1,
               unsigned char r, unsigned char g, unsigned char b);

void draw_circle(pixel *img, int w, int h,
                 int cx, int cy, int radius,
                 unsigned char r, unsigned char g, unsigned char b,
                 int fill);

void draw_char(pixel *img, int w, int h,
               int x, int y, char c,
               unsigned char r, unsigned char g, unsigned char b);

void draw_char_scaled(pixel *img, int w, int h,
                      int x, int y, char c,
                      unsigned char r, unsigned char g, unsigned char b,
                      int scale);

#endif