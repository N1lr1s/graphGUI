#include "Graph.h"
#include "Renderer.h"

void Graph::Draw(Renderer& renderer)
{
    for (double i = -10.0; i <= 10.0; i += 0.1) {
        double y1 = F(i);
		double y2 = F(i + 0.1);

		renderer.DrawLine(i, y1, i + 0.1, y2);
    }
}

double Graph::F(double x) const
{
    return m_function.Parabola(x);
}