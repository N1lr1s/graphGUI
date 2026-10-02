#pragma once
#include "CoordinateSystem.h"
#include "Graph.h"

#include <Windows.h>

class Renderer
{
public:

    Graph m_graph;
    explicit Renderer(HDC hdc);

    void Draw(HWND hwnd);
    void DrawLine(double x1, double y1, double x2, double y2);

private:

    CoordinateSystem m_coord;
    void DrawGrid(RECT rc);
    void DrawAxes(RECT rc);
    void DrawGraph(RECT rc);
    void DrawText();

    HDC m_hdc;
};