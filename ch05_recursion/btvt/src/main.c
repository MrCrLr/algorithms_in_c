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
    image_t *img = calloc(1, sizeof *img);
    if (!img) {
        perror("calloc image");
        exit(EXIT_FAILURE);
    }
    
    img->w = 800;
    img->h = 500;

    img->data = calloc(img->w * img->h, sizeof *img->data);
    if (!img->data) {
        perror("calloc pixel data");
        free(img);
        exit(EXIT_FAILURE);
    }
    pixel bg_color = {0};

    for (int y = 0; y < img->h; y++) {
        for (int x = 0; x < img->w; x++) {
            bg_color.r = (uint8_t)(100);
            bg_color.g = (uint8_t)((x * 200) / (img->w - 1));
            bg_color.b = (uint8_t)((y * 255) / (img->h - 1));
            set_pixel(img, x, y, bg_color);
        }
    }

    // Print a longer sentence
    int scale = 2;
    const char *msg = "Hello there world, this is a long message that needs wrapping.";
    pixel white = {255, 255, 255};
    draw_paragraph_scaled(img, 50, 50, msg, white, scale);

    // Print a single word
    int c_scale = 6; // Choose you text scaling. Higher is bigger :)
    int c_size = 8 * c_scale;
    const char *word = "\x02 MrCrLr \x02";
    int c_num = strlen(word);

    // Center string on page horizontally and vertically
    int start_x = (img->w - c_num * c_size) / 2; // Each letter 1:1 8px
    int start_y = (img->h - c_size) / 2; 
    pixel fg_color = { .r = 255, .g = 255, .b = 0 }; // Choose your text color

    for (int i = 0; word[i] != '\0'; i++) {
        draw_char_scaled(img, start_x + i * (c_size), start_y,
                         word[i], fg_color, c_scale);
    }

    write_bmp("btvt_test5.bmp", img);
    
    free(img->data);
    free(img);

    return 0;
}
