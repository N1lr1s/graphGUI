#include "GoldenSection.h"

#include <cmath>

std::vector<Iteration> GoldenSection::Run(
    const Function& function,
    double a,
    double b,
    double eps) const
{

    std::vector<Iteration> history;
    int index = 0;

    while (fabs(b - a) > eps)
    {
        history.push_back(
            {
                index++,
                a,
                b,
            });
        
        double c = a + 0.382 * (b - a);

        if (function.Parabola(a) * function.Parabola(c) < 0) {
            b = c;
        }
        else {
            a = c;
        }
    }

    history.push_back(
        {
            index,
            a,
            b,
        });

    return history;
}