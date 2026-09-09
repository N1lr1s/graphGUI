#define UNICODE
#define _UNICODE

#include <windows.h>
#include <math.h>

const wchar_t CLASS_NAME[] = L"MainWindowClass";


double F(double x) {
    return 0.01 * pow(x, 2);
}

void drawPoint(HDC hdc, int centerX, int centerY, double x, double y, double scaleX, double scaleY) {
    int screenX = centerX + (x * scaleX);
    int screenY = centerY - (y * scaleY);

    Ellipse(hdc, screenX - 2, screenY - 2, screenX + 2, screenY + 2);
}

void drawCords(HDC hdc, int centerX, int centerY) {
    MoveToEx(hdc, 0, centerY, NULL);
    LineTo(hdc, 800, centerY);

    MoveToEx(hdc, centerX, 0, NULL);
    LineTo(hdc, centerX, 600);
}

void drawGraphic(HDC hdc, int centerX, int centerY) {

    double scaleX = 2;
    double scaleY = 5;

    drawCords(hdc, centerX, centerY);

    for (double x = -200; x <= 200; x += (1.0 / scaleX)) {
        drawPoint(hdc, centerX, centerY, x, F(x), scaleX, scaleY);
    }
}



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

        // Текст

        HFONT hFont = CreateFontW(
            36,
            0,
            0,
            0,
            FW_SEMIBOLD,
            FALSE,
            FALSE,
            FALSE,
            DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            L"Segoe UI"
        );

        HFONT oldFont = (HFONT)SelectObject(hdc, hFont);

        TextOutW(hdc, 50, 10, L"Графический калькулятор", 23);

        SelectObject(hdc, oldFont);
        DeleteObject(hFont);

        //Рисование графика

        HPEN hPen = CreatePen(PS_SOLID, 2, RGB(100, 0, 0));

        HBRUSH hBrush = CreateSolidBrush(RGB(254, 0, 0));

        HPEN oldPen = (HPEN)SelectObject(hdc, hPen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

        RECT rc;
        GetClientRect(hwnd, &rc);

        int width = rc.right;
        int height = rc.bottom;

        int centerX = width / 2;
        int centerY = height / 2;
        drawGraphic(hdc, centerX, centerY);

        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);

        DeleteObject(hPen);
        DeleteObject(hBrush);


        // Конец рисования

        EndPaint(hwnd, &ps);
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
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    if (!RegisterClassW(&wc))
        return -1;

    HWND hwnd = CreateWindowExW(
        0,                      // расширенный стиль
        CLASS_NAME,             // имя класса
        L"GraphCalc",           // заголовок
        WS_OVERLAPPEDWINDOW,    // стиль окна
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        800,
        600,
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