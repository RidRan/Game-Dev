#include <windows.h>

HBITMAP imageToBitmap(COLORREF *image, int width, int height) {
     CreateBitmap(width, height, 1, 8*4, (void*) image);
}