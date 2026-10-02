#include "GoldenSection.h"

#include <cmath>

std::vector<Iteration> GoldenSection::Run(
    const Function& function,
    double a,
    double b,
    double eps) const
{
    const double PHI = (std::sqrt(5.0) - 1.0) / 2.0;

    std::vector<Iteration> history;

    double x1 = b - PHI * (b - a);
    double x2 = a + PHI * (b - a);

    double f1 = function.Parabola(x1);
    double f2 = function.Parabola(x2);

    int index = 0;

    while ((b - a) > eps)
    {
        history.push_back(
            {
                index++,
                a,
                b,
                x1,
                x2,
                f1,
                f2
            });

        if (f1 <= f2)
        {
            b = x2;

            x2 = x1;
            f2 = f1;

            x1 = b - PHI * (b - a);
            f1 = function.Parabola(x1);
        }
        else
        {
            a = x1;

            x1 = x2;
            f1 = f2;

            x2 = a + PHI * (b - a);
            f2 = function.Parabola(x2);
        }
    }

    history.push_back(
        {
            index,
            a,
            b,
            x1,
            x2,
            f1,
            f2
        });

    return history;
}