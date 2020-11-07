#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void AddMenus(HWND);

void gradientDraw(HWND);

HMENU hMenu;

int WINAPI WinMain(HINSTANCE inst,
                     HINSTANCE prevInst,
                     LPSTR cmdLine,
                     int cmdShow) {
                         
    MessageBox(NULL, "This application is still in very early stages of development.", "Disclaimer", MB_OK);
    
    WNDCLASSEX wc;
    HWND wnd;
    MSG msg;

    const char *className = "RatGameWindowClass";

    wc.cbClsExtra     = 0;
    wc.cbSize         = sizeof(WNDCLASSEX);
    wc.cbWndExtra     = 0;

    wc.hInstance      = inst;
    wc.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm        = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW);

    wc.lpfnWndProc    = WndProc;
    wc.lpszMenuName   = NULL;
    wc.lpszClassName  = className;

    wc.style          = CS_DBLCLKS;

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    wnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        className,
        "Window Test",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,         //w   h
        100, 100, 1280, 700,
        NULL, NULL, inst, NULL);

    if(wnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while(GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

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

void gradientDraw(HWND hwnd) {
    RECT size;
    GetWindowRect(hwnd, &size);
    int width = size.right - size.left;
    int height = size.bottom - size.top;
    COLORREF color = 0x00000000;

    COLORREF *arr = (COLORREF*) calloc(width*height, sizeof(COLORREF));
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            arr[i*width + j] = color;
            color++;
        }
    }

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