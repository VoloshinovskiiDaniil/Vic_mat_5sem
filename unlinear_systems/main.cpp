#include "functions.h"
#include<fstream>
#include<cmath>

double func_1(double x) 
{
	return (x * x + tan(x) * tan(x) - 1);
}
double func_2(double x) 
{
	if (x >= 0)
	{
		return (x - tan(sqrt(1 - x * x)));
	}
	else
	{
		return (x + tan(sqrt(1 - x * x)));
	}
}

int main()
{
	std::cout.precision(6);
	std::cout << "1st solution:		" << "x = " << solve(func_1, -0.2, 0.5, 10) << "	" << "y = " << solve(func_2, -0.2, 0.5, 10) << std::endl;
	std::cout << "2nd solution:		" << "x = " << solve(func_1, 0.2, -0.5, 10) << "	" << "y = " << solve(func_2, -0.2, -0.5, 10) << std::endl;

///////////////////////////////////////////////////////////////////////////////////////

	const unsigned int N = 4;
	const double M = 0.7853981633974483;
	std::array<double, 4> eсс {0.1, 0.2, 0.5, 0.8};
	//std::array<double, 4> E {0.8612648848681753, 0.9478282237995903, 1.261703055253102, 1.585313861354208};
	std::array<double, 4> E{ 0.861264884868175, 0.947828223799590, 1.26170305525310, 1.58531386135421};
	std::ofstream data_point1("data1.txt");
	data_point1.precision(10);
	for (int i = 1; i < 10; i++)
	{
		data_point1 << i << "		" << log10(abs(E[0] - keplerSolver(eсс[0], M, i, 0))) << std::endl;
	}
	data_point1.close();


	std::ofstream data_point2("data2.txt");
	data_point2.precision(16);
	for (int i = 1; i < 10; i++)
	{
		data_point2 << i << "		" << log10(abs(E[1] - keplerSolver(eсс[1], M, i, 0))) << std::endl;
	}
	data_point2.close();

	std::ofstream data_point5("data5.txt");
	data_point5.precision(16);
	for (int i = 1; i < 10; i++)
	{
		data_point5 << i << "		" << log10(abs(E[2] - keplerSolver(eсс[2], M, i, 0))) << std::endl;
	}
	data_point5.close();

	std::ofstream data_point8("data8.txt");
	data_point8.precision(16);
	for (int i = 1; i < 10; i++)
	{
		data_point8 << i << "		" << log10(abs(E[3] - keplerSolver(eсс[3], M, i, 0))) << std::endl;
	}
	data_point8.close();


	return 0;
}
