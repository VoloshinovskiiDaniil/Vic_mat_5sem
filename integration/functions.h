#pragma once

#include<iostream>
#include <array>
#include <type_traits>


template <typename RealType, unsigned int N> struct nodes;

template <typename RealType> struct nodes<RealType, 3> 
{
    static constexpr std::array<RealType, 3> points {-0.7745966692, 0, 0.7745966692};
    static constexpr std::array<RealType, 3> weights {0.5555555556, 0.8888888889, 0.5555555556};
};

template <typename RealType> struct nodes<RealType, 5> 
{
    static constexpr std::array<RealType, 5> points {-0.9061798459, -0.5384693101, 0, 0.5384693101, 0.9061798459};
    static constexpr std::array<RealType, 5> weights {0.2369268851, 0.4786286705, 0.5688888889, 0.4786286705, 0.2369268851};
};

template<typename A>
struct ArgumentGetter;

template<typename R, typename Arg>
struct ArgumentGetter<R(Arg)> 
{
    using Argument = Arg;
};

template<typename T>
using Dif = decltype(std::declval<T>() - std::declval<T>());

template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(
    const Callable& func,
    const typename ArgumentGetter<Callable>::Argument& start,
    const typename ArgumentGetter<Callable>::Argument& end,
    const std::array<RealType, N>& points,
    const std::array<RealType, N>& weights
)
{
    RealType Int_step = 0;
    RealType shift = (end + start) / 2;
    RealType wide = (end - start) / 2;

    for (int i = 0; i < N; i++)
    {
        Int_step += wide * func(shift + wide * points[i]) * weights[i];
    }

    return Int_step;
};

template<typename Callable, typename RealType, std::size_t N>
decltype(auto) integrate(
    const Callable& func,
    const typename ArgumentGetter<Callable>::Argument& start,
    const typename ArgumentGetter<Callable>::Argument& end, 
    const std::array<RealType, N>& points, 
    const std::array<RealType, N>& weights,
    const Dif<typename ArgumentGetter<Callable>::Argument>& dx 
)
{
    unsigned int number = (end - start) / dx;
    double dx_norm = (end - start) / number;

    RealType Int = 0;

    for (int i = 0; i < number; i++)
    {
        Int += integrate<Callable, RealType, N>(func, start + i * dx_norm, start + (i + 1) * dx_norm, points, weights);
    }

    return Int;
};
