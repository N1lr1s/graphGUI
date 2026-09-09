#pragma once
#include <Windows.h>

struct PointD
{
    double x;
    double y;
};

class CoordinateSystem
{
public:

    CoordinateSystem();

    void SetViewportSize(int width, int height);

    POINT WorldToScreen(double x, double y) const;

    PointD ScreenToWorld(int x, int y) const;

private:

    double m_scale = 40.0;

    double m_originX = 0.0;
    double m_originY = 0.0;

    int m_width = 0;
    int m_height = 0;
};