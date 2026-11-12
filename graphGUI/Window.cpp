#define UNICODE

#include "Window.h"

const wchar_t CLASS_NAME[] = L"MainWindowClass";

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        Renderer renderer(hdc);
        renderer.Draw(hwnd);

        EndPaint(hwnd, &ps);
        return 0;
    }
	break;
	case WM_SIZE:
    {
		InvalidateRect(hwnd, nullptr, TRUE);
		return 0;
    }
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int RunApplication(HINSTANCE hInstance, int nCmdShow){

    WNDCLASSW wc = {};

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hbrBackground = (HBRUSH)(COLOR_SCROLLBAR + 1);

    if (!RegisterClassW(&wc))
        return -1;

    HWND hwnd = CreateWindowExW(
        0,                      // расширенный стиль
        CLASS_NAME,             // имя класса
        L"GraphCalc",           // заголовок
        WS_OVERLAPPEDWINDOW,    // стиль окна
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1020,
        920,
        nullptr,
        nullptr,
        hInstance,
        nullptr);

    if (hwnd == nullptr)
        return -1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {};

    while (GetMessageW(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return (int)msg.wParam;
}