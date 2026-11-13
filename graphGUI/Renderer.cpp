
#include "Renderer.h"

Renderer::Renderer(HDC hdc, CoordinateSystem& coord)
	: m_hdc(hdc),
	m_coord(coord)
{
}

void Renderer::Draw(HWND hwnd, const Layout& m_layout, CoordinateSystem& m_coord)
{
    RECT rc;
    GetClientRect(hwnd, &rc);
	RECT plot = m_layout.GetPlotRect();
	RECT control = m_layout.GetControlRect();
	RECT status = m_layout.GetStatusRect();
	RECT graph = m_layout.GetGraphRect();

    m_coord.SetViewport(plot);

    DrawInterface(graph, control, status);

    DrawGrid(plot);
    DrawAxes(rc, plot);
    m_graph.Draw(*this, plot);

    std::vector<Iteration> hist = m_goldenSection.Run(m_graph.m_function, 0.0, 3.0, 0.01);
//    if (!isPainted) DrawGoldenSection(hist);

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
	}
    isPainted = true;
}

void Renderer::DrawAxes(RECT rc, RECT plot)
{
	SetPen(RGB(0, 0, 0), 2);
    POINT left = m_coord.WorldToScreen(-100, 0);
    POINT right = m_coord.WorldToScreen(100, 0);
    POINT top = m_coord.WorldToScreen(0, -100);
    POINT bot = m_coord.WorldToScreen(0, 100);

	BeginClip(plot);

/*
    MoveToEx(m_hdc, left.x, 10, nullptr);
    LineTo(m_hdc, left.x, 570);

    MoveToEx(m_hdc, right.x, 10, nullptr);
    LineTo(m_hdc, right.x, 570);

    MoveToEx(m_hdc, 10, top.y, nullptr);
    LineTo(m_hdc, 570, top.y);

    MoveToEx(m_hdc, 10, bot.y, nullptr);
    LineTo(m_hdc, 570, bot.y);
    */
    MoveToEx(m_hdc, left.x, left.y, nullptr);
    LineTo(m_hdc, right.x, right.y);
    
    MoveToEx(m_hdc, top.x, top.y, nullptr);
    LineTo(m_hdc, bot.x, bot.y);
    /*
	for (int i = -10; i <= 10; i += 1)
	{
		POINT p1 = m_coord.WorldToScreen(i, -0.1);
		POINT p2 = m_coord.WorldToScreen(i, 0.1);
		MoveToEx(m_hdc, p1.x, p1.y, nullptr);
		LineTo(m_hdc, p2.x, p2.y);
	}

    for (int j = -10; j <= 10.0; j += 1)
    {
        POINT t1 = m_coord.WorldToScreen(-0.1, j);
        POINT t2 = m_coord.WorldToScreen(0.1, j);
        MoveToEx(m_hdc, t1.x, t1.y, nullptr);
        LineTo(m_hdc, t2.x, t2.y);
    }
    */
    SetPen(RGB(0, 0, 0), 1);
	EndClip();
}

void Renderer::DrawText(RECT rc)
{

}

void Renderer::DrawLine(double x1, double y1, double x2, double y2) {

    POINT p1 = m_coord.WorldToScreen(x1, y1);
    POINT p2 = m_coord.WorldToScreen(x2, y2);

	MoveToEx(m_hdc, p1.x, p1.y, nullptr);
	LineTo(m_hdc, p2.x, p2.y);
}

void Renderer::DrawGrid(RECT plot)
{
    BeginClip(plot);

    SetPen(RGB(200, 200, 200), 1);


    for (double x = -20; x <= 20; x += 1)
    {
        POINT p1 = m_coord.WorldToScreen(x, -20);
        POINT p2 = m_coord.WorldToScreen(x, 20);

        MoveToEx(m_hdc, p1.x, p1.y, nullptr);
        LineTo(m_hdc, p2.x, p2.y);
    }

    for (double y = -20; y <= 20; y += 1)
    {
        POINT p1 = m_coord.WorldToScreen(-20, y);
        POINT p2 = m_coord.WorldToScreen(20, y);

        MoveToEx(m_hdc, p1.x, p1.y, nullptr);
        LineTo(m_hdc, p2.x, p2.y);
    }
    SetPen(RGB(0, 0, 0), 1);
    EndClip();
}

void Renderer::DrawInterface(RECT plot, RECT control, RECT status) {

    DrawFrame(plot);
	SetBrush(RGB(240, 240, 240));
    DrawFrame(control);

    DrawFrame(status);
    SetBrush(RGB(255, 255, 255));
}

void Renderer::DrawFrame(const RECT& rect) {
	Rectangle(m_hdc, rect.left, rect.top, rect.right, rect.bottom);
}


// Перо и кисть для рисования


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

void Renderer::SetBrush(COLORREF color)
{
    if (m_brush != nullptr)
    {
        SelectObject(m_hdc, m_oldBrush);
        DeleteObject(m_brush);
    }
    m_brush = CreateSolidBrush(color);
    SelectObject(m_hdc, m_brush);
}

void Renderer::ResetBrush()
{
	if (m_brush != nullptr)
	{
		SelectObject(m_hdc, m_oldBrush);
		DeleteObject(m_brush);
		m_brush = nullptr;
		m_oldBrush = nullptr;
	}
}


//Обрезка области вывода графика

void Renderer::BeginClip(const RECT& plot)
{
	SaveDC(m_hdc);

	IntersectClipRect(
		m_hdc,
		plot.left,
		plot.top,
		plot.right,
		plot.bottom);
}

void Renderer::EndClip()
{
	RestoreDC(m_hdc, -1);
}