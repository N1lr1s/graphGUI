#pragma once

#include <Windows.h>

class Layout
{
public:

    void Update(HWND hwnd);

    RECT GetGraphRect() const;
    RECT GetControlRect() const;
    RECT GetStatusRect() const;
	RECT GetPlotRect() const;

private:

	RECT m_plot{};
    RECT m_graph{};
    RECT m_control{};
    RECT m_status{};
};