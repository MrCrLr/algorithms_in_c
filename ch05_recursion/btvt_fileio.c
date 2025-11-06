#include "btvt_fileio.h"

void write_bmp(const char *path, pixel *img, int width, int height) {
    FILE *f = fopen(path, "wb");
    if (!f) exit(EXIT_FAILURE);

    int bits_per_pixel = 24;
    int bytes_per_pixel = bits_per_pixel / 8;
    
    uint32_t row_size = (width * bytes_per_pixel + 3) & (~3); // bitmask zeroes out lower 2 bits
    uint32_t pixel_array_size = row_size * height;
    uint32_t file_size = 14 + 40 + pixel_array_size;

    // bitmap file header
    unsigned char file_header[14] = {
        'B','M',
        file_size, file_size>>8, file_size>>16, file_size>>24,
        0,0,0,0,
        54,0,0,0
    };
    fwrite(file_header, 1, 14, f);

    // bitmap info header
    unsigned char info_header[40] = {0};
    info_header[0] = 40;
    info_header[4] = width; info_header[5] = width>>8;
    info_header[6] = width>>16; info_header[7] = width>>24;
    info_header[8] = height; info_header[9] = height>>8;
    info_header[10] = height>>16; info_header[11] = height>>24;
    info_header[12] = 1; info_header[14] = bits_per_pixel;
    fwrite(info_header, 1, 40, f);

    // write pixel data, each row padded to 4 bytes
    unsigned char pad[3] = {0, 0, 0};
    int pad_bytes = bmp_pad_bytes(width, bytes_per_pixel);

    for (int y = height - 1; y >= 0; y--) {
        fwrite(&img[y * width], 3, width, f);
        fwrite(pad, 1, pad_bytes, f);
    }

    fclose(f);
}

static inline int bmp_pad_bytes(int width, int bytes_per_pixel) {
    return (4 - (width * bytes_per_pixel) % 4) % 4;
}