#pragma once

#include <iostream>
#include <array>
#include <cmath>


template <typename RealType, unsigned int N>
std::array<RealType, N> uniform_grid(const RealType first, const RealType last)
{
    std::array<RealType, N> grid_points;
    double step = (last - first) / (N - 1);

    for (unsigned int i = 0; i < N; i++)
    {
        grid_points[i] = first + i*step;
    }
    return grid_points;
};

template <typename RealType, unsigned int N>
std::array<RealType, N> chebyshev_grid(const RealType first, const RealType last)
{
    const double pi = 3.141592653589793;
    double shift = (first + last) / 2;
    double wide = (last - first) / 2;
    
    std::array<RealType, N> grid_points;

    for (unsigned int i = 0; i < N; i++)
    {
         grid_points[i] = shift + wide * cos(pi * (2 * (N - i) - 1) / (2 * N));
    }

    return grid_points;
}


template<typename xType, typename yType, unsigned int N>
class NewtonInterpolator
{
private:

    std::array<yType, N> coeffs;
    std::array<xType, N> grid;

public:

    NewtonInterpolator(const std::array<xType, N>& points, const std::array<yType, N>& values) noexcept
       // grid{points}, coeffs{values}
    {
        for (unsigned i = 0; i < N; i++)
        {
            grid[i] = points[i];
            coeffs[i] = values[i];
        }
        for (unsigned int i = 0; i < N; i++)
        {
            for (unsigned int j = N - 1; j > i; j--)
            {
                coeffs[j] = (coeffs[j] - coeffs[j - 1]) / (grid[j] - grid[j - i - 1]);
            }
        }
    };

    yType interpolate(const xType& x) const noexcept
    {
        yType y;
        yType y_pr;

        y = 0;
        for (unsigned int i = 0; i < N; i++)
        {
            y_pr = coeffs[i];
            for (unsigned int j = 0; j < i; j++)
            {
                y_pr *= (x - grid[j]);
            }
            y += y_pr;
        }

        return y;
    }
};
