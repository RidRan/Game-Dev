#include <windows.h>
#include <stdio.h>

#include "imageUtils.h"

COLORREF *screen;

COLORREF *getScreen() {
    return screen;
}

COLORREF *loadImageFromBMP(char *filepath, int *width, int *height) {
    FILEHEADER fh;
    INFOHEADER ih;

    FILE *instream = fopen(filepath, "rb");

    fread(&fh, sizeof(COLORREF), sizeof(FILEHEADER), instream);
    fread(&ih, sizeof(COLORREF), sizeof(INFOHEADER), instream);
    *width = ih.width;
    *height = ih.height;

    COLORREF *image = (COLORREF *) calloc(*width * *height, sizeof(COLORREF));

    fseek(instream, fh.offset, 0);
    for (int i = 0; i < *height; i++){
        for (int j = 0; j < *width; j++) {
            fread(&image[i * *width + j], sizeof(unsigned char), sizeof(COLORREF), instream);
        }
    }
    
    return image;
}

HBITMAP imageToBitmap(COLORREF *image, int width, int height) {
    HBITMAP map = CreateBitmap(width, height, 1, 8*4, (void*) image);
    free(image);
    return map;
}