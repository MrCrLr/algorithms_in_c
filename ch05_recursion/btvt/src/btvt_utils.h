#ifndef BTVT_UTILS_H
#define BTVT_UTILS_H

#include "btvt_types.h"
#include "btvt_fonts.h"

void set_pixel(pixel *img, int w, int h, int x, int y, pixel color);

void draw_line(pixel *img, int w, int h, int x0, int y0, int x1, int y1, 
               pixel color);

void draw_circle(pixel *img, int w, int h, int cx, int cy, int radius, 
                 pixel color, int fill);

void draw_char(pixel *img, int w, int h, int x, int y, 
               char c, pixel color);

void draw_char_scaled(pixel *img, int w, int h, int x, int y, 
                      char c, pixel color, int scale);

#endif
