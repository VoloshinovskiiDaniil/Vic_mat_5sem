#pragma once

#include<iostream>
#include <array>

struct IterationException {};

double keplerSolver(double ecc, double meanAnomaly, unsigned int maxIter, double tol)
{
    double E = meanAnomaly + ecc * sin(meanAnomaly) / (1 - ecc * cos(meanAnomaly));
    double delta = abs(meanAnomaly - E);

    for (int i = 1; (i < maxIter) and (delta > tol); i++) 
    {
        delta = E;
        E = E - (E - ecc * sin(E) - meanAnomaly) / (1 - ecc * cos(E));
        delta = abs(E - delta);
        if (i == maxIter)
        {
            throw IterationException();
        }
    }

    return E;
};



template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> {
    using Argument = Arg;
};

template<typename Callable, typename RealType>
decltype(auto) solve(
    const Callable& func,                                             
    const RealType& tau,                                              
    const typename ArgumentGetter<Callable>::Argument& initialGuess,  
    const unsigned int nIteration                                     
)
{
    double x = initialGuess;

    for (int i = 0; i < nIteration; i++)
    {
        x += tau * func(x);
    }

    return x;

};
