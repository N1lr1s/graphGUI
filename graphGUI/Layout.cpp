#include "Layout.h"

void Layout::Update(HWND hwnd)
{
    RECT rc;
    GetClientRect(hwnd, &rc);

    const int margin = 10;
    const int controlWidth = 280;
    const int statusHeight = 130;
	const int padding = 10;

    m_plot = m_graph;

    m_plot.left += padding;
    m_plot.top += padding;
    m_plot.right -= padding;
    m_plot.bottom -= padding;

    m_graph.left = margin;
    m_graph.top = margin;
    m_graph.right = rc.right - controlWidth - margin * 2;
    m_graph.bottom = rc.bottom - statusHeight - margin;

    m_control.left = m_graph.right + margin;
    m_control.top = margin;
    m_control.right = rc.right - margin;
    m_control.bottom = m_graph.bottom;

    m_status.left = margin;
    m_status.top = m_graph.bottom + margin;
    m_status.right = rc.right - margin;
    m_status.bottom = rc.bottom - margin;
}

RECT Layout::GetGraphRect() const
{
    return m_graph;
}

RECT Layout::GetControlRect() const
{
    return m_control;
}

RECT Layout::GetStatusRect() const
{
    return m_status;
}

RECT Layout::GetPlotRect() const
{
    return m_plot;
}