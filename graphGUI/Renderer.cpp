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

    DrawGrid(rc);
    DrawAxes(rc);
    DrawGraph(rc);
    DrawText();
}

void Renderer::DrawAxes(RECT rc)
{
    int cx = (rc.right - rc.left) / 2;
    int cy = (rc.bottom - rc.top) / 2;

    MoveToEx(m_hdc, 0, cy, nullptr);
    LineTo(m_hdc, rc.right, cy);

    MoveToEx(m_hdc, cx, 0, nullptr);
    LineTo(m_hdc, cx, rc.bottom);
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

void Renderer::DrawGrid(RECT)
{
}

void Renderer::DrawGraph(RECT)
{
}