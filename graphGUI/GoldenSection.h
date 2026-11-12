#pragma once

#include "Function.h"
#include "Iteration.h"

#include <vector>
#include <cmath>

class GoldenSection
{
public:

    std::vector<Iteration> Run(
        const Function& function,
        double a,
        double b,
        double eps
    ) const;
};