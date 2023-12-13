#include <functions.h>
#include<cmath>
#include<fstream>

Eigen::Vector<double, 1> lin(const Eigen::Vector<double, 1> state, const double t)
{
    Eigen::Vector<double, 1> res;
    res = Eigen::Vector < double, 1>::Zero();
    res[0] = t * t * t;
    return(res);
}
double ans1(double t) 
{ 
    return (t * t * t * t / 4); 
}
Eigen::Vector<double, 2> osc(const Eigen::Vector<double, 2> state, const double t) 
{
    Eigen::Vector<double, 2> res = {state[1], (-1) * state[0]};
    return(res);
}
double ans2(double t) 
{
    return (sin(t)); 
}


СauchyProblem<decltype(lin), 1> linear;
СauchyProblem<decltype(osc), 2> oscillator;

int main() 
{
    const double start = 0;
    const double end = 5;

    std::ofstream data1("data1.txt");
    data1.precision(16);
    std::ofstream data2("data2.txt");
    data2.precision(16);

    for (double h = -14; h < 0; h += 0.5) 
    {
        double step = exp(h);

        auto res1 = integrate<decltype(lin), BDF4, СauchyProblem<decltype(lin), 1>, RK4Table>(lin, {Eigen::Vector<double, 1>(0.0), start}, end, {step, 1e-6, 10}, linear);
        double err1 = (res1[0].state[0] - ans1(start));

        double delta;
        for (unsigned int i = 1; i < res1.size(); i++) 
        {
            delta = abs(res1[i].state[0] - ans1(res1[i].arg));
            if (delta > err1)
            {
                err1 = delta;
            }
        }

        auto res2  = integrate<decltype(osc), BDF4, СauchyProblem<decltype(osc), 2>, RK4Table>(osc, {Eigen::Vector<double, 2>(0.0, 1.0), start}, end, {step, 1e-6, 10 }, oscillator);
        double err2 = (res2[0].state[0] - ans2(start));

        for (unsigned int i = 1; i < res2.size(); i++)
        {
            delta = abs(res2[i].state[0] - ans2(res2[i].arg));
            if (delta > err2)
            {
                err2 = delta;
            }
        }

        data1 << h << "     " << log(err1) << std::endl;
        data2 << h << "     " << log(err2) << std::endl;
    }

    data1.close();
    data2.close();

    return 0;
};
