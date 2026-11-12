#include "CoordinateSystem.h"

CoordinateSystem::CoordinateSystem()
{
    m_scale = 40;

    m_width = 800;
    m_height = 300;

    m_originX = 290;
    m_originY = 290;
}

void CoordinateSystem::SetViewport(const RECT& rect)
{
    m_width = rect.right - rect.left;
    m_height = rect.bottom - rect.top;

	m_originX = rect.left + m_width / 2.0;
	m_originY = rect.top + m_height / 2.0;
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