#include "Renderer.h"
#include "Function.h"
#include <math.h>
#include <iostream>
#include <string>

Renderer::Renderer(HDC hdc)
    : m_hdc(hdc)
{
}

void Renderer::Draw(HWND hwnd)
{
    RECT rc;
    GetClientRect(hwnd, &rc);
	Function function;
	GoldenSection goldenSection;
	std::vector<Iteration> hist = goldenSection.Run(function, 0.0, 3.0, 0.01);
	m_coord.SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);
    DrawGrid(rc);
    DrawAxes(rc);
    m_graph.Draw(*this);
    if (!isPainted) DrawGoldenSection(hist);
    DrawText(rc);
	ResetPen();
}

void Renderer::DrawGoldenSection(std::vector<Iteration>& hist) {
	int Color = 150;
    int count = 0;
	while (!hist.empty() && count < 6) {
		const Iteration& iter = hist.front();
		hist.erase(hist.begin());
		POINT p11 = m_coord.WorldToScreen(iter.a, -1);
		POINT p21 = m_coord.WorldToScreen(iter.b, -1);
        POINT p12 = m_coord.WorldToScreen(iter.a, 1);
        POINT p22 = m_coord.WorldToScreen(iter.b, 1);
        SetPen(RGB(Color, 0, 0), 2);
		MoveToEx(m_hdc, p11.x, p11.y, nullptr);
		LineTo(m_hdc, p12.x, p12.y);
        SetPen(RGB(0, 0, Color), 2);
        MoveToEx(m_hdc, p21.x, p21.y, nullptr);
        LineTo(m_hdc, p22.x, p22.y);
		Color += 20;
        count++;
		Sleep(1500);
	}
    isPainted = true;
}

void Renderer::DrawAxes(RECT rc)
{
    POINT left = m_coord.WorldToScreen(-10, 0);
    POINT right = m_coord.WorldToScreen(10, 0);
    POINT top = m_coord.WorldToScreen(0, -10);
    POINT bot = m_coord.WorldToScreen(0, 10);

    MoveToEx(m_hdc, left.x, 10, nullptr);
    LineTo(m_hdc, left.x, 570);

    MoveToEx(m_hdc, right.x, 10, nullptr);
    LineTo(m_hdc, right.x, 570);

    MoveToEx(m_hdc, 10, top.y, nullptr);
    LineTo(m_hdc, 570, top.y);

    MoveToEx(m_hdc, 10, bot.y, nullptr);
    LineTo(m_hdc, 570, bot.y);

    MoveToEx(m_hdc, left.x, left.y, nullptr);
    LineTo(m_hdc, right.x, right.y);

	for (int i = -10; i <= 10; i += 1)
	{
		POINT p1 = m_coord.WorldToScreen(i, -0.1);
		POINT p2 = m_coord.WorldToScreen(i, 0.1);
		MoveToEx(m_hdc, p1.x, p1.y, nullptr);
		LineTo(m_hdc, p2.x, p2.y);
	}

    MoveToEx(m_hdc, top.x, top.y, nullptr);
    LineTo(m_hdc, bot.x, bot.y);

    for (int j = -10; j <= 10.0; j += 1)
    {
        POINT t1 = m_coord.WorldToScreen(-0.1, j);
        POINT t2 = m_coord.WorldToScreen(0.1, j);
        MoveToEx(m_hdc, t1.x, t1.y, nullptr);
        LineTo(m_hdc, t2.x, t2.y);
    }
}

void Renderer::DrawText(RECT rc)
{
    TextOutW(
        m_hdc,
        700,
        20,
        L"Количество корней: ",
        20
    );
    TextOutW(
        m_hdc,
        700,
        50,
        L"Корень: ",
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

void Renderer::SetPen(COLORREF color, int width)
{
    if (m_pen != nullptr)
    {
        SelectObject(m_hdc, m_oldPen);
        DeleteObject(m_pen);
    }

    m_pen = CreatePen(PS_SOLID, width, color);
    m_oldPen = (HPEN)SelectObject(m_hdc, m_pen);
}

void Renderer::ResetPen()
{
    if (m_pen != nullptr)
    {
        SelectObject(m_hdc, m_oldPen);
        DeleteObject(m_pen);
        m_pen = nullptr;
        m_oldPen = nullptr;
    }
}