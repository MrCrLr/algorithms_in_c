#ifndef BTVT_TYPES_H
#define BTVT_TYPES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Core pixel type (shared by everything)
typedef struct {
    unsigned char b, g, r;
} pixel;

#endif