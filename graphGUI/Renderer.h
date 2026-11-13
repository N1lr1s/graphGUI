#pragma once
#include <windows.h>

#include "CoordinateSystem.h"
#include "Graph.h"
#include "GoldenSection.h"
#include "Layout.h"
#include "Controls.h"

#include <math.h>
#include <iostream>
#include <string>

class Renderer
{
public:

    Layout m_layout;
    Graph m_graph;
    GoldenSection m_goldenSection;
    explicit Renderer(HDC hdc, CoordinateSystem& coord);

    void Draw(HWND hwnd, const Layout& m_layout, CoordinateSystem& m_coord);
    void DrawLine(double x1, double y1, double x2, double y2);
    void BeginClip(const RECT& plot);
    void EndClip();
    void SetPen(COLORREF color, int width = 1);
    void ResetPen();

    void SetBrush(COLORREF color);
	void ResetBrush();

private:

    bool isPainted = false;

	CoordinateSystem& m_coord;

	HPEN m_pen = nullptr;
	HPEN m_oldPen = nullptr;
	HBRUSH m_brush = nullptr;
	HBRUSH m_oldBrush = nullptr;

    void DrawGrid(RECT rc);
    void DrawAxes(RECT rc, RECT plot);
    void DrawGraph(RECT rc);
    void DrawGoldenSection(std::vector<Iteration>& hist);
	void DrawInterface(RECT plot, RECT control, RECT status);
    void DrawFrame(const RECT& rect);
    void DrawText(RECT rc);

    HDC m_hdc;

};