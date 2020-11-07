#include <windows.h>

#include "windowRunnerUtils.h"

HMENU hMenu;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_PAINT:
            
            break;
        case WM_COMMAND:
            switch(wParam) {
                case 1:
                    MessageBeep(MB_OK);
                    gradientDraw(hwnd);
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

    // Creating temp bitmap
    HBITMAP map = CreateBitmap(width, // width. 512 in my case
                            height, // height
                            1, // Color Planes, unfortanutelly don't know what is it actually. Let it be 1
                            8*4, // Size of memory for one pixel in bits (in win32 4 bytes = 4*8 bits)
                            (void*) arr); // pointer to array
    // Temp HDC to copy picture
    HDC hdc = GetDC(hwnd);
    HDC src = CreateCompatibleDC(hdc); // hdc - Device context for window, I've got earlier with GetDC(hWnd) or GetDC(NULL);
    SelectObject(src, map); // Inserting picture into our temp HDC
    // Copy image from temp HDC to window
    BitBlt(hdc, // Destination
        0,  // x and
        0,  // y - upper-left corner of place, where we'd like to copy
        width, // width of the region
        height, // height
        src, // source
        0,   // x and
        0,   // y of upper left corner  of part of the source, from where we'd like to copy
        SRCCOPY); // Defined DWORD to juct copy pixels. Watch more on msdn;

    DeleteDC(src); // Deleting temp HDC
    DeleteDC(hdc);
    free(arr);
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