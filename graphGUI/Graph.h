#pragma once
#include "Function.h"

class Renderer;

class Graph
{
public:

    Function m_function;
    void Draw(Renderer& renderer);

private:

    double F(double x) const;
};
