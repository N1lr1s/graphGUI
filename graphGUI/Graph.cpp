#include "Graph.h"
#include "Renderer.h"

void Graph::Draw(Renderer& renderer, const RECT& plot)
{
	renderer.SetPen(RGB(255, 0, 0), 2);
	renderer.BeginClip(plot);
    for (double i = -20.0; i <= 20.0; i += 0.1) {
        double y1 = F(i);
		double y2 = F(i + 0.1);

		renderer.DrawLine(i, y1, i + 0.1, y2);
    }
	renderer.SetPen(RGB(0, 0, 0), 1);
	renderer.EndClip();
}

double Graph::F(double x) const
{
    return m_function.Parabola(x);
}