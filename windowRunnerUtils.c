#include <windows.h>

#include "windowRunnerUtils.h"
#include "imageUtils.h"

HMENU hMenu;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_PAINT:
            
            break;
        case WM_COMMAND:
            switch(wParam) {
                case 1:
                    MessageBeep(MB_OK);
                    int width, height;
                    drawBitmap(hwnd, imageToBitmap(loadImageFromBMP("avery.bmp", &width, &height), width, height));

                    break;
                default:
                    break;
            }
            break;
        case WM_CREATE:
            AddMenus(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

void AddMenus(HWND hwnd) {
    hMenu = CreateMenu();

    AppendMenu(hMenu, MF_STRING, 1, "Draw Gradient");

    SetMenu(hwnd, hMenu);
}

void drawBitmap(HWND hwnd, HBITMAP map) {
    HDC hdc = GetDC(hwnd);
    HDC src = CreateCompatibleDC(hdc);
    SelectObject(src, map);

    BitBlt(hdc, 0,  0, getWidth(hwnd), getHeight(hwnd), src, 0, 0, SRCCOPY);
    DeleteDC(src);
    DeleteDC(hdc);
}

int getWidth(HWND hwnd) {
    RECT size;
    GetWindowRect(hwnd, &size);
    return size.right - size.left;
}

int getHeight(HWND hwnd) {
    RECT size;
    GetWindowRect(hwnd, &size);
    return size.bottom - size.top;;
}