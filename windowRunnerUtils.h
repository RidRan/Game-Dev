#include <windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

void drawBitmap(HWND, HBITMAP);

int getWidth(HWND);

int getHeight(HWND);