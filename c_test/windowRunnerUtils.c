#include <windows.h>
#include <time.h>
#include <stdio.h>

#include "windowRunnerUtils.h"
#include "imageUtils.h"

HMENU hMenu;

clock_t currentClock = 0;
int frameCount = 0;
int fps = 1;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (clock() - currentClock >= CLOCKS_PER_SEC / fps) {
        currentClock = clock();
        byte *image = NULL;
        int width, height, bytesPerPixel;
        loadImageFromBMP("avery.bmp",&image, &width, &height, &bytesPerPixel);
        drawFitBitmap(hwnd, CreateBitmap(width, height, 1, 8*4, (void *) byteToCOLORREF(image, width, height, bytesPerPixel)), width, height);

    }
    switch(msg) {
        case WM_PAINT:
            
            break;
        case WM_COMMAND:
            switch(wParam) {
                case 1:
                    {
                    byte *image = NULL;
                    int width, height, bytesPerPixel;
                    loadImageFromBMP("avery.bmp",&image, &width, &height, &bytesPerPixel);
                    drawBitmap(hwnd, CreateBitmap(width, height, 1, 8*4, (void *) byteToCOLORREF(image, width, height, bytesPerPixel)));
                    break;
                    }
                case 2:
                    {
                    byte *image = NULL;
                    int width, height, bytesPerPixel;
                    loadImageFromBMP("avery.bmp",&image, &width, &height, &bytesPerPixel);
                    drawFitBitmap(hwnd, CreateBitmap(width, height, 1, 8*4, (void *) byteToCOLORREF(image, width, height, bytesPerPixel)), width, height);
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

    AppendMenu(hMenu, MF_STRING, 1, "Draw Avery");

    AppendMenu(hMenu, MF_STRING, 2, "Draw Avery (Fit)");

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

void drawFitBitmap(HWND hwnd, HBITMAP map, int width, int height) {
    if (map == NULL) {
        fprintf(stderr, "NULL HBITMAP received!\n");
    }

    HDC hdc = GetDC(hwnd);
    HDC src = CreateCompatibleDC(hdc);
    SelectObject(src, map);
    SetStretchBltMode(hdc, HALFTONE);
    StretchBlt(hdc, 0,  0, getWidth(hwnd), getHeight(hwnd), src, 0, 0, width, height, SRCCOPY);
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