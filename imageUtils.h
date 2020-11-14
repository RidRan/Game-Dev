#include <windows.h>

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0

typedef unsigned int int32;
typedef short int16;
typedef unsigned char byte;

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

void loadImageFromBMP(char *, byte **, int *, int *, int *);

void WriteImage(const char *, byte *, int, int,int);

HBITMAP imageToBitmap(byte *, int, int, int);