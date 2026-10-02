#pragma once
#include <vector>
#include "Function.h"
#include "Iteration.h"

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