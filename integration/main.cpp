#include "functions.h"
#include <fstream>
#include <cmath>

double function(double x)
{
	return sin(x); 
}

double function_int(double x)
{
	return -cos(x);
}

int main()
{
	const double start = 0;
	const double end = 10;

	std::ofstream data3("data3.txt");
	data3.precision(15);
	std::ofstream data5("data5.txt");
	data5.precision(15);

	const double I = function_int(end) - function_int(start);
	for (double h = -5; h < 5; h += 0.1)
	{
		data3 << h << "  " << log(abs(I - integrate<decltype(function), double, 3>(function, start, end, nodes<double, 3>::points, nodes<double, 3>::weights, exp(h)))) << std::endl;
		data5 << h << "  " << log(abs(I - integrate<decltype(function), double, 5>(function, start, end, nodes<double, 5>::points, nodes<double, 5>::weights, exp(h)))) << std::endl;
	}

    data3.close();
    data5.close();

    return 0;
}
