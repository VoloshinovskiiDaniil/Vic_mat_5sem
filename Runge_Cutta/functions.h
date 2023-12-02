#pragma once

#include<iostream>
#include<vector>
#include<array>
#include<Eigen\Dense>


struct RK4Table {
    static constexpr unsigned int stages = 4;
    static constexpr std::array<std::array<double, stages>, stages> table = {0.0, 0.0, 0.0, 0.0,
                                                                             0.5, 0.0, 0.0, 0.0,
                                                                             0.0, 0.5, 0.0, 0.0,
                                                                             0.0, 0.0, 1.0, 0.0};
    static constexpr std::array<double, stages> cColumn = {0, 0.5, 0.5, 1};
    static constexpr std::array<double, stages> bString = {1.0 / 6, 1.0 / 3, 1.0 / 3, 1.0 / 6};
};

class Polinom {
public:
    static constexpr unsigned int dim = 1;
    using State = Eigen::Vector<double, 1>;
    using Argument = double;

    struct StateAndArg {
        State state;
        Argument arg;
    };

    Eigen::Vector<double, 1> calc(const State& state, const Argument arg) const
    {
        Eigen::Vector<double, 1> res;
        res[0] = arg * arg * arg;
        return res;
    };
};

class Oscillator {
public:
    static constexpr unsigned int dim = 2;
    using State = Eigen::Vector<double, 2>;
    using Argument = double;

    struct StateAndArg {
        State state;
        Argument arg;
    };

    Eigen::Vector<double, 2> calc(const State& state, const Argument arg) const
    {
        Eigen::Vector<double, 2> res;
        res[0] = state[1];
        res[1] = (-1) * state[0];
        return res;
    };
};

template<typename Table, typename RHS>
std::vector<std::array<double, 2>> integrate(
    const typename RHS::State& initialState,
    const typename RHS::Argument& startTime,
    const typename RHS::Argument& endTime,
    double step,
    const RHS& rhs)
{
    const unsigned int dim = RHS::dim;
    const unsigned int stages = Table::stages;

    Eigen::Vector<double, dim> state = initialState;
    double arg = startTime;
    Eigen::Matrix<double, dim, stages> k;

    const unsigned int N = (endTime - startTime) / step + 1;
    step = (endTime - startTime) / N;

    std::vector<std::array<double, 2>> res;
    res.push_back({state[0], arg});

    for (unsigned int n = 0; n < N; n++)
    {
        for (int i = 0; i < stages; i++)
        {
            Eigen::Vector<double, dim> y = state;
            for (int j = 0; j < i; j++)
            {
                y += Table::table[i][j] * k.col(j);
            }
            k.col(i) = step * rhs.calc(y, arg + step * Table::cColumn[i]);
        }

        Eigen::Vector < double, dim> delta_y;
        delta_y = Eigen::Vector < double, dim>::Zero();
        for (int i = 0; i < stages; i++)
        {
            delta_y += Table::bString[i] * k.col(i);
        }

        state += delta_y;
        arg += step;
        res.push_back({state[0], arg});
    }

    return res;
}
