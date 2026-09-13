#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem()
{
    m_scale = 40;

    m_width = 800;
    m_height = 600;

    m_originX = 400;
    m_originY = 300;
}

void CoordinateSystem::SetViewportSize(int width, int height)
{
    m_width = width;
    m_height = height;

	m_originX = width / 2.0;
	m_originY = height / 2.0;
}

POINT CoordinateSystem::WorldToScreen(double x, double y) const
{
    POINT p;

    p.x = static_cast<LONG>(m_originX + x * m_scale);

    p.y = static_cast<LONG>(m_originY - y * m_scale);

    return p;
}

PointD CoordinateSystem::ScreenToWorld(int x, int y) const
{
    PointD p;

    p.x = (x - m_originX) / m_scale;

    p.y = (m_originY - y) / m_scale;

    return p;
}