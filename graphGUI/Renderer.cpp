#include "Renderer.h"
#include <math.h>

Renderer::Renderer(HDC hdc)
    : m_hdc(hdc)
{
}

void Renderer::Draw(HWND hwnd)
{
    RECT rc;
    GetClientRect(hwnd, &rc);

	m_coord.SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

    DrawGrid(rc);
    DrawAxes(rc);
    DrawGraph(rc);
    DrawText();
}

void Renderer::DrawAxes(RECT rc)
{
    POINT left = m_coord.WorldToScreen(-100, 0);
    POINT right = m_coord.WorldToScreen(100, 0);
    POINT top = m_coord.WorldToScreen(0, 100);
    POINT bot = m_coord.WorldToScreen(0, -100);

    MoveToEx(m_hdc, left.x, left.y, nullptr);
    LineTo(m_hdc, right.x, right.y);

	for (int i = -100; i <= 100; i += 1)
	{
		POINT p1 = m_coord.WorldToScreen(i, -0.1);
		POINT p2 = m_coord.WorldToScreen(i, 0.1);
		MoveToEx(m_hdc, p1.x, p1.y, nullptr);
		LineTo(m_hdc, p2.x, p2.y);
	}

    MoveToEx(m_hdc, top.x, top.y, nullptr);
    LineTo(m_hdc, bot.x, bot.y);

    for (int j = -100; j <= 100; j += 1)
    {
        POINT t1 = m_coord.WorldToScreen(-0.1, j);
        POINT t2 = m_coord.WorldToScreen(0.1, j);
        MoveToEx(m_hdc, t1.x, t1.y, nullptr);
        LineTo(m_hdc, t2.x, t2.y);
    }
}

void Renderer::DrawText()
{
    TextOutW(
        m_hdc,
        20,
        20,
        L"GraphCalc",
        9
    );
}

void Renderer::DrawLine(double x1, double y1, double x2, double y2) {

    POINT p1 = m_coord.WorldToScreen(x1, y1);
    POINT p2 = m_coord.WorldToScreen(x2, y2);

	MoveToEx(m_hdc, p1.x, p1.y, nullptr);
	LineTo(m_hdc, p2.x, p2.y);
}

void Renderer::DrawGrid(RECT)
{
}

void Renderer::DrawGraph(RECT)
{
    for (int i = -10; i <= 10; i += 0.1) {

    }
}