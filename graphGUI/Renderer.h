#pragma once

#include <Windows.h>

class Renderer
{
public:

    explicit Renderer(HDC hdc);

    void Draw(HWND hwnd);

private:

    void DrawGrid(RECT rc);
    void DrawAxes(RECT rc);
    void DrawGraph(RECT rc);
    void DrawText();

    HDC m_hdc;
};