#pragma once
#include "Function.h"
#include <windows.h>

class Renderer;

class Graph
{
public:
    
    Function m_function;
    void Draw(Renderer& renderer, const RECT& plot);

private:

    double F(double x) const;
};
