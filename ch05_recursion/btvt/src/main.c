// BINARY TREE VISUALIZATION TOOL (btvt)
// Save binary tree visualization to a bmp file
/*
clang -std=c11 -Wall -Wextra -pedantic src/main.c \
src/btvt_fileio.c src/btvt_fonts.c src/btvt_utils.c \
-o build/btvt
*/

#include "btvt_fileio.h"
#include "btvt_types.h"
#include "btvt_utils.h"

int main(void) 
{

    int w = 800;
    int h = 500;
    
    // each pixel rendered into an array of 'pixel' structs
    pixel *img = calloc(w * h, sizeof(pixel));
    pixel color = {0};

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            color.r = (uint8_t)(100);
            color.g = (uint8_t)((x * 200) / (w - 1));
            color.b = (uint8_t)((y * 255) / (h - 1));
            set_pixel(img, w, h, x, y, color);
        }
    }
    
    int scale = 4;
    const char *word = "\x02 CYBORG \x02";
    int length = strlen(word);
    
    // Center string on page horizontally and vertically
    int start_x = w / 2 - ((length / 2) * (8 * scale)); // Each letter 1:1 8px
    int start_y = h / 2 - (8 * scale / 2); 
    pixel text_color = { .r = 255, .g = 255, .b = 255 };// initialize text color

    for (int i = 0; word[i] != '\0'; i++) {
        draw_char_scaled(img, w, h, start_x + i * (8 * scale), start_y,
                         word[i], text_color, scale);
    }

    write_bmp("btvt_test.bmp", img, w, h);
    free(img);

    return 0;
}
