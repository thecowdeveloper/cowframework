#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK
MainWindowCallback(
    HWND Window,
    UINT Message,
    WPARAM wParam,
    LPARAM lParam
) {
    LRESULT Result = 0;

    switch (Message) {
    case WM_SIZE:
    {
        printf("window size\n");
    }break;

    case WM_DESTROY:
    {
        OutputDebugStringA("window destroy\n");
    }break;

    case WM_CLOSE:
    {
        OutputDebugStringA("window close\n");
    }break;

    case WM_ACTIVATEAPP:
    {
        OutputDebugStringA("activate app\n");
    }break;

    default:
    {
        Result = DefWindowProc(Window, Message, wParam, lParam);
    }break;
    }
    return(Result);
}

int CALLBACK WinMain(HINSTANCE Instance,
    HINSTANCE PrevInstance,
    LPSTR CommandLine,
    int ShowCode)
{
    WNDCLASS WindowClass = { 0 };
    WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
    WindowClass.lpfnWndProc = MainWindowCallback;
    WindowClass.hInstance = Instance;
    //    WindowClass.hIcon = ;
    WindowClass.lpszClassName = "AdrianWindowClass";

    if (RegisterClass(&WindowClass)) {
        HWND WindowHandle =
            CreateWindowEx(
                0,
                WindowClass.lpszClassName,
                "Adrian's app",
                WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                CW_USEDEFAULT,
                0,
                0,
                Instance,
                0);
        if (WindowHandle != 0) {

            for (;;) {
                MSG Message;
                BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
                if (MessageResult > 0) {
                    TranslateMessage(&Message);
                    DispatchMessage(&Message);
                }
            }
        }
    }

    return(0);
}
