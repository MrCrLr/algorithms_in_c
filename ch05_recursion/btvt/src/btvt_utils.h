#ifndef BTVT_UTILS_H
#define BTVT_UTILS_H

#include "btvt_types.h"
#include "btvt_fonts.h"

void set_pixel(image_t *img, int x, int y, pixel color);

void draw_line(image_t *img, int x0, int y0, int x1, int y1, pixel color);

void draw_circle(image_t *img, int cx, int cy, int radius, pixel color, int fill);

void draw_char(image_t *img, int x, int y, char c, pixel color);

void draw_char_scaled(image_t *img, int x, int y, char c, pixel color, int scale);

void draw_string_scaled(image_t *img, int x, int y, const char *text, pixel color, int scale);

void draw_paragraph_scaled(image_t *img, int x, int y, const char *text, pixel color, int scale);

char **split_lines(const char *text, int max_chars_per_line, int *out_line_count);

#endif
