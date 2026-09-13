#pragma once

class Renderer;

class Graph
{
public:

    void Draw(Renderer& renderer);

private:

    double F(double x) const;
};
