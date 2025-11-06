#ifndef BTVT_FILEIO_H
#define BTVT_FILEIO_H

#include "btvt_types.h"

void write_bmp(const char *path, pixel *img, int width, int height);

static inline int bmp_pad_bytes(int width, int bytes_per_pixel);

#endif 