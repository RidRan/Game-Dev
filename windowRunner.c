#include <windows.h>

#include "windowRunnerUtils.h"

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