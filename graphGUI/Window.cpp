#define UNICODE

#include "Window.h"

const wchar_t CLASS_NAME[] = L"MainWindowClass";


Window::Window()
{
}

bool Window::Create(HINSTANCE hInstance, int nCmdShow)
{
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
        0,
        CLASS_NAME,
        L"GraphCalc",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1020,
        920,
        nullptr,
        nullptr,
        hInstance,
        this);

    if (hwnd == nullptr)
        return -1;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    return true;
}

int Window::MessageLoop()
{
	MSG msg = {};
	while (GetMessageW(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	Window* window = nullptr;
	if (msg == WM_NCCREATE) {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);

		window = static_cast<Window*>(cs->lpCreateParams);

		SetWindowLongPtrW(
			hwnd,
			GWLP_USERDATA,
			reinterpret_cast<LONG_PTR>(window));

		window->m_hwnd = hwnd;
	}
	else {
		window = reinterpret_cast<Window*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
	}

	if (window) {
		return window->HandleMessage(msg, wParam, lParam);
	}
}


LRESULT Window::HandleMessage(UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_GETMINMAXINFO: {
		LPMINMAXINFO lpMMI = (LPMINMAXINFO)lParam;
		lpMMI->ptMinTrackSize.x = 400;
		lpMMI->ptMinTrackSize.y = 310;
		break;
	}
	case WM_CREATE:

		m_controls.Create(m_hwnd);
		return 0;

	case WM_DESTROY:

		PostQuitMessage(0);
		return 0;

	case WM_PAINT:
	{
		PAINTSTRUCT ps;

		HDC hdc = BeginPaint(m_hwnd, &ps);

		Renderer renderer(hdc, m_coord);
		renderer.Draw(m_hwnd, m_layout, m_coord);

		EndPaint(m_hwnd, &ps);

		return 0;
	}
	case WM_SIZE:
	{
		m_layout.Update(m_hwnd);

		m_controls.Resize(m_layout.GetControlRect());
		InvalidateRect(m_hwnd, nullptr, TRUE);

		return 0;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case ID_BUTTON_RUN:
		{
			double a = m_controls.GetA();
			double b = m_controls.GetB();
			return 0;
		}
		}
		break;
	}
	case WM_MOUSEWHEEL:
	{
		int delta = GET_WHEEL_DELTA_WPARAM(wParam);

		if (delta > 0)
			m_coord.Zoom(1.1);

		else
			m_coord.Zoom(0.9);

		InvalidateRect(m_hwnd, nullptr, TRUE);
		return 0;
	}
	}
	return DefWindowProc(m_hwnd, msg, wParam, lParam);
}