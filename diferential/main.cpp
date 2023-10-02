#include<functions.h>
#include<fstream>


int main()
{
	const double x0 = 1;
	const std::array< double, 16> step = { 1, 1e-1, 1e-2, 1e-3, 1e-4, 1e-5, 1e-6, 1e-7, 1e-8, 1e-9, 1e-10, 1e-11, 1e-12, 1e-13, 1e-14, 1e-15 };

	std::ofstream check("check.txt");
	check.precision(15);

	for (int i = 0; i < 16; i++)
	{
		check << step[i] << "	" << dif<double, 2>(x0, step[i], { -1, 1 }) << std::endl;
	}

	check.close();

	double graf_step[1000];
	graf_step[0] = -15 * log(10);

	for (int i = 1; i < 1000; i++)
	{
		double delta = abs(graf_step[0]) / 1000;
		graf_step[i] = graf_step[i - 1] + delta;
	}

	std::ofstream data3("data3.txt");
	data3.precision(15);

	for (double x : graf_step)
	{
		data3 << x << " " << log(abs(dif<double, 3>(x0, exp(x), { -1, 1, 2 }) - exp(x0))) << std::endl;
	}

	data3.close();

	std::ofstream data4("data4.txt");
	data4.precision(15);

	for (double x : graf_step)
	{
		data4 << x << " " << log(abs(dif<double, 4>(x0, exp(x), { -2, -1, 1, 2 }) - exp(x0))) << std::endl;
	}

	data4.close();

	std::ofstream data5("data5.txt");
	data5.precision(15);

	for (double x : graf_step)
	{
		data5 << x << " " << log(abs(dif<double, 5>(x0, exp(x), { -2, -1, 1, 2, 3 }) - exp(x0))) << std::endl;
	}

	data5.close();

	return 0;
}
