#ifndef BTVT_FILEIO_H
#define BTVT_FILEIO_H

#include <errno.h>
#include <libgen.h>         // dirname()
#include <limits.h>         // PATH_MAX
#include <sys/stat.h>
#include <unistd.h>         // readlink()

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#include "btvt_types.h"

void write_bmp(const char *filename, image_t *img);

#endif
