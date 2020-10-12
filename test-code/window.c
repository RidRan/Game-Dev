#include <windows.h>
#include <stdio.h>
#include <time.h>

const char g_szClassName[] = "myWindowClass";

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;                 // device context (DC) for window  
    RECT rcTmp;              // temporary rectangle  
    PAINTSTRUCT ps;          // paint data for BeginPaint and EndPaint  
    POINT ptClientUL;        // client area upper left corner  
    POINT ptClientLR;        // client area lower right corner  
    static HDC hdcCompat;    // DC for copying bitmap  
    POINT pt;
    LPPOINT lppt;         // x and y coordinates of cursor  
    static RECT rcBmp;       // rectangle that encloses bitmap  
    static RECT rcTarget;    // rectangle to receive bitmap  
    static RECT rcClient;    // client-area rectangle  
    static BOOL fDragRect;   // TRUE if bitmap rect. is dragged  
    static HBRUSH hbrBkgnd;  // handle of background-color brush  
    static COLORREF crBkgnd; // color of client-area background  
    static HPEN hpenDot;     // handle of dotted pen

    COLORREF color=RGB(255,0,0);

    char mouseHeld = 0;

    switch(msg)
    {
        case WM_LBUTTONDOWN:
        {
            mouseHeld = 1;
            // GetCursorPos(&pt);
            // 
            // hdc = GetDC(hwnd);
            // SetPixel(hdc, pt.x, pt.y, color);
        break;
        }
        case WM_LBUTTONUP:
        {
            mouseHeld = 0;
        break;
        }
        case WM_PAINT:
                GetCursorPos(&pt);
                hdc = GetDC(hwnd);
                // printf("Cursor position: %d,%d\n", pt.x, pt.y);
                SetPixel(hdc, pt.x, pt.y, color);
        break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Window Test",
        WS_OVERLAPPEDWINDOW,         //w   h
        CW_USEDEFAULT, CW_USEDEFAULT, 1280, 700,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Step 3: The Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}