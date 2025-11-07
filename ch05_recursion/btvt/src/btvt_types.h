#ifndef BTVT_TYPES_H
#define BTVT_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Core pixel type (shared by everything)
typedef struct {
    uint8_t b, g, r;
} pixel;

#endif
