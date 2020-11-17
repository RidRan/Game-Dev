#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

void drawBitmap(HWND, HBITMAP);

void drawImage(HWND, byte *, int, int, int);

int getWidth(HWND);

int getHeight(HWND);