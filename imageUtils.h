#include <windows.h>

typedef struct
{
    WORD type;  //specifies the file type
    DWORD size;  //specifies the size in bytes of the bitmap file
    WORD reserved1;  //reserved; must be 0
    WORD reserved2;  //reserved; must be 0
    DWORD offset;  //species the offset in bytes from the bitmapfileheader to the bitmap bits
} FILEHEADER;

typedef struct
{
    DWORD size;  //specifies the number of bytes required by the struct
    LONG width;  //specifies width in pixels
    LONG height;  //species height in pixels
    WORD planes; //specifies the number of color planes, must be 1
    WORD bitCount; //specifies the number of bit per pixel
    DWORD compression;//spcifies the type of compression
    DWORD sizeImage;  //size of image in bytes
    LONG xPelsPerMeter;  //number of pixels per meter in x axis
    LONG yPelsPerMeter;  //number of pixels per meter in y axis
    DWORD clrUsed;  //number of colors used by th ebitmap
    DWORD clrImportant;  //number of colors that are important
} INFOHEADER;

COLORREF *getScreen();

COLORREF *loadImageFromBMP(char *filepath, int *width, int *height);

HBITMAP imageToBitmap(COLORREF *, int, int);