#pragma once
#include "CoordinateSystem.h"
#include "Graph.h"
#include "GoldenSection.h"

#include <Windows.h>

class Renderer
{
public:

    Graph m_graph;
    explicit Renderer(HDC hdc);

    void Draw(HWND hwnd);
    void DrawLine(double x1, double y1, double x2, double y2);

private:

	void SetPen(COLORREF color, int width = 1);
	void ResetPen();

	HPEN m_pen = nullptr;
	HPEN m_oldPen = nullptr;

    CoordinateSystem m_coord;
    void DrawGrid(RECT rc);
    void DrawAxes(RECT rc);
    void DrawGraph(RECT rc);
    void DrawGoldenSection(std::vector<Iteration>& hist);
    void DrawText(RECT rc);

    HDC m_hdc;
};