// BINARY TREE VISUALIZATION TOOL (btvt)
// Save binary tree visualization to a bmp file
#include "btvt_fileio.h"
#include "btvt_types.h"
#include "btvt_utils.h"

int main(void) 
{

    int w = 800;
    int h = 500;
    
    // each pixel redenered into an array of 'pixel' structs
    pixel *img = calloc(w * h, sizeof(pixel));

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            unsigned char r = (unsigned char)(100);
            unsigned char g = (unsigned char)((x * 200) / (w - 1));
            unsigned char b = (unsigned char)((y * 255) / (h - 1));
            set_pixel(img, w, h, x, y, r, g, b);
        }
    }
    
    int scale = 4;
    const char *word = "\x02 CYBORG \x02";
    int length = strlen(word);
    
    // Center string on page horizontally and vertically
    int start_x = w / 2 - ((length / 2) * (8 * scale)); // Each letter at 1:1 is 8px
    int start_y = h / 2 - (8 * scale / 2); 
    unsigned char r = 255, g = 255, b = 255; // initialize text color

    for (int i = 0; word[i] != '\0'; i++) {
        draw_char_scaled(img, w, h, start_x + i * (8 * scale), start_y,
                         word[i], r, g, b, scale);
    }

    write_bmp("btvt_test.bmp", img, w, h);
    free(img);

    return 0;
}



