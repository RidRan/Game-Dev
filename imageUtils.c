#include <windows.h>

COLORREF *screen;

HBITMAP imageToBitmap(COLORREF *image, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

        }
    }
    HBITMAP map = CreateBitmap(width, height, 1, 8*4, (void*) image);
    free(image);
    return map;
}