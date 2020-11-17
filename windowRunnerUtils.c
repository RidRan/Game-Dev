#include <windows.h>
#include <stdio.h>

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
                    {
                    MessageBeep(MB_OK);
                    byte *image = NULL;
                    int width, height, bytesPerPixel;
                    loadImageFromBMP("avery.bmp",&image, &width, &height, &bytesPerPixel);
                    // WriteImage("screen.bmp", image, width, height, bytesPerPixel);
                    //drawBitmap(hwnd, (HBITMAP) LoadImageW(NULL, L"screen.bmp", IMAGE_BITMAP, width, height, LR_LOADFROMFILE));
                    // drawBitmap(hwnd, CreateBitmap(width, height, 1, 8*bytesPerPixel, image));
                    drawBitmap(hwnd, CreateBitmap(width, height, 1, 8*4, (void *) byteToCOLORREF(image, width, height, bytesPerPixel)));
                    // drawBitmap(hwnd, CreateBitmap(width, height, 1, 8*4, (void *) getBlackCOLORREF(width, height)));
                    break;
                    }
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
    if (map == NULL) {
        fprintf(stderr, "NULL HBITMAP received!\n");
    }

    HDC hdc = GetDC(hwnd);
    HDC src = CreateCompatibleDC(hdc);
    SelectObject(src, map);

    BitBlt(hdc, 0,  0, getWidth(hwnd), getHeight(hwnd), src, 0, 0, SRCCOPY);
    DeleteDC(src);
    DeleteDC(hdc);
}

void drawImage(HWND hwnd, byte *image, int width, int height, int bytesPerPixel) {
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