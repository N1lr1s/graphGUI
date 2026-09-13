#pragma once
#include "CoordinateSystem.h"

#include <Windows.h>

class Renderer
{
public:

    explicit Renderer(HDC hdc);

    void Draw(HWND hwnd);

private:

    CoordinateSystem m_coord;
    void DrawGrid(RECT rc);
    void DrawAxes(RECT rc);
    void DrawLine(double x1, double y1, double x2, double y2);
    void DrawGraph(RECT rc);
    void DrawText();

    HDC m_hdc;
};