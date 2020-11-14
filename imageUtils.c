#include <windows.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "imageUtils.h"



COLORREF *screen;

COLORREF *getScreen() {
    return screen;
}

void loadImageFromBMP(char *filepath, byte **image, int *width, int *height, int *bytesPerPixel) {

    FILE *imageFile = fopen(filepath, "rb");
    int dataOffset;
    fseek(imageFile, DATA_OFFSET_OFFSET, SEEK_SET);
    fread(&dataOffset, 4, 1, imageFile);
    fseek(imageFile, WIDTH_OFFSET, SEEK_SET);
    fread(width, 4, 1, imageFile);
    fseek(imageFile, HEIGHT_OFFSET, SEEK_SET);
    fread(height, 4, 1, imageFile);
    int16 bitsPerPixel;
    fseek(imageFile, BITS_PER_PIXEL_OFFSET, SEEK_SET);
    fread(&bitsPerPixel, 2, 1, imageFile);
    *bytesPerPixel = ((int)bitsPerPixel) / 8;

    int paddedRowSize = (int)(4 * ceil((float)(*width) / 4.0f))*(*bytesPerPixel);
    int unpaddedRowSize = (*width)*(*bytesPerPixel);
    int totalSize = unpaddedRowSize*(*height);
    *image = (byte*)malloc(totalSize);
    int i = 0;
    byte *currentRowPointer = *image+((*height-1)*unpaddedRowSize);
    for (i = 0; i < *height; i++)
    {
            fseek(imageFile, dataOffset+(i*paddedRowSize), SEEK_SET);
        fread(currentRowPointer, 1, unpaddedRowSize, imageFile);
        currentRowPointer -= unpaddedRowSize;
    }

    fclose(imageFile);
}

void WriteImage(const char *fileName, byte *pixels, int width, int height,int bytesPerPixel)
{
        //Open file in binary mode
        FILE *outputFile = fopen(fileName, "wb");
        //*****HEADER************//
        //write signature
        const char *BM = "BM";
        fwrite(&BM[0], 1, 1, outputFile);
        fwrite(&BM[1], 1, 1, outputFile);
        //Write file size considering padded bytes
        int paddedRowSize = (int)(4 * ceil((float)width/4.0f))*bytesPerPixel;
        int fileSize = paddedRowSize*height + HEADER_SIZE + INFO_HEADER_SIZE;
        fwrite(&fileSize, 4, 1, outputFile);
        //Write reserved
        int reserved = 0x0000;
        fwrite(&reserved, 4, 1, outputFile);
        //Write data offset
        int dataOffset = HEADER_SIZE+INFO_HEADER_SIZE;
        fwrite(&dataOffset, 4, 1, outputFile);

        //*******INFO*HEADER******//
        //Write size
        int infoHeaderSize = INFO_HEADER_SIZE;
        fwrite(&infoHeaderSize, 4, 1, outputFile);
        //Write width and height
        fwrite(&width, 4, 1, outputFile);
        fwrite(&height, 4, 1, outputFile);
        //Write planes
        int16 planes = 1; //always 1
        fwrite(&planes, 2, 1, outputFile);
        //write bits per pixel
        int16 bitsPerPixel = bytesPerPixel * 8;
        fwrite(&bitsPerPixel, 2, 1, outputFile);
        //write compression
        int compression = NO_COMPRESION;
        fwrite(&compression, 4, 1, outputFile);
        //write image size (in bytes)
        int imageSize = width*height*bytesPerPixel;
        fwrite(&imageSize, 4, 1, outputFile);
        //write resolution (in pixels per meter)
        int resolutionX = 11811; //300 dpi
        int resolutionY = 11811; //300 dpi
        fwrite(&resolutionX, 4, 1, outputFile);
        fwrite(&resolutionY, 4, 1, outputFile);
        //write colors used 
        int colorsUsed = MAX_NUMBER_OF_COLORS;
        fwrite(&colorsUsed, 4, 1, outputFile);
        //Write important colors
        int importantColors = ALL_COLORS_REQUIRED;
        fwrite(&importantColors, 4, 1, outputFile);
        //write data
        int i = 0;
        int unpaddedRowSize = width*bytesPerPixel;
        for ( i = 0; i < height; i++)
        {
                //start writing from the beginning of last row in the pixel array
                int pixelOffset = ((height - i) - 1)*unpaddedRowSize;
                fwrite(&pixels[pixelOffset], 1, paddedRowSize, outputFile);	
        }
        fclose(outputFile);
}

HBITMAP imageToBitmap(byte *image, int width, int height, int bytesPerPixel) {
    return CreateBitmap(width, height, 1, bytesPerPixel*4, image);
}