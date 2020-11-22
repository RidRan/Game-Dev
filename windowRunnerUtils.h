#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

void drawBitmap(HWND, HBITMAP);

void drawFitBitmap(HWND, HBITMAP, int, int);

void drawImage(HWND, byte *, int, int, int);

int getWidth(HWND);

int getHeight(HWND);