#include <functions.h>
#include <cmath>
#include<fstream>

Polinom polinom;
Oscillator oscillator;

double sol1(double t)
{
    return (t * t * t * t / 4); 
}
double sol2(double t)
{
    return (sin(t));
}

int main(){
    const double start = 0;
    const double end = 5;

    std::ofstream data1("data1.txt");
    data1.precision(16);
    std::ofstream data2("data2.txt");
    data2.precision(16);

    for (double h = -14; h < 0; h += 0.5)
    {
        double step = exp(h);
        double delta;

        std::vector<std::array<double, 2>> res1 = integrate< RK4Table, Polinom>(Eigen::Vector<double, 1>(0.0), start, end, step, polinom);
        double eps1 = abs(res1[0][0] - sol1(res1[0][1]));
        for (unsigned int i = 1; i < res1.size(); i++)
        {
            delta = abs(res1[i][0] - sol1(res1[i][1]));
            if (delta > eps1)
            {
                eps1 = delta;
            }
        }

        std::vector<std::array<double, 2>> res2 = integrate<RK4Table, Oscillator>(Eigen::Vector<double, 2>(0.0, 1.0), start, end, step, oscillator);
        double eps2 = abs(res2[0][0] - sol2(res2[0][1]));
        for (unsigned int i = 1; i < res2.size(); i++)
        {
            delta = abs(res2[i][0] - sol2(res2[i][1]));
            if (delta > eps2)
            {
                eps2 = delta;
            }
        }

        data1 << h << "     " << log(eps1) << std::endl;
        data2 << h << "     " << log(eps2) << std::endl;
    }

    data1.close();
    data2.close();

    return 0;
};