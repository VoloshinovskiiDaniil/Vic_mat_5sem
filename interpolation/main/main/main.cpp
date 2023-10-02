#include "functions.h"
#include<fstream>
#include<cmath>


int main()
{
	const unsigned int s = 1000;
	const double first = 0;
	const double last = 2;
	const double step = 0.0001;


	std::ofstream data3_un("data3_uniform.txt");
	data3_un.precision(15);
	std::ofstream data3_ch("data3_chebyshev.txt");
	data3_ch.precision(15);

	for (double len = step; len < last - first; len += step)
	{
		std::array<double, 3> x_un = uniform_grid<double, 3>(first, first + len);
		std::array<double, 3> y_un;

		for (unsigned int i = 0; i < 3; i++)
		{
			y_un[i] = exp(x_un[i]);
		}

		NewtonInterpolator<double, double, 3> un_interp3(x_un, y_un);
		double epsilon = 0;

		for (double x = first; x < len; x += len / s)
		{
			double delta = abs(un_interp3.interpolate(x) - exp(x));
			if (delta > epsilon)
			{
				epsilon = delta;
			}
		}

		data3_un << log(len) << "	" << log(epsilon) << std::endl;


		std::array<double, 3> x_ch = chebyshev_grid<double, 3>(first, first + len);
		std::array<double, 3> y_ch;

		for (unsigned int i = 0; i < 3; i++)
		{
			y_ch[i] = exp(x_ch[i]);
		}

		NewtonInterpolator<double, double, 3> ch_interp3(x_ch, y_ch);
		epsilon = 0;

		for (double x = first; x < len; x += len / s)
		{
			double delta = abs(ch_interp3.interpolate(x) - exp(x));
			if (delta > epsilon)
			{
				epsilon = delta;
			}
		}

		data3_ch << log(len) << "	" << log(epsilon) << std::endl;
	}

	data3_un.close();
	data3_ch.close();


	std::ofstream data4_un("data4_uniform.txt");
	data4_un.precision(15);
	std::ofstream data4_ch("data4_chebyshev.txt");
	data4_ch.precision(15);

	for (double len = step; len < last - first; len += step)
	{
		std::array<double, 4> x_un = uniform_grid<double, 4>(first, first + len);
		std::array<double, 4> y_un;

		for (unsigned int i = 0; i < 4; i++)
		{
			y_un[i] = exp(x_un[i]);
		}

		NewtonInterpolator<double, double, 4> un_interp4(x_un, y_un);
		double epsilon = 0;

		for (double x = first; x < len; x += len / s)
		{
			double delta = abs(un_interp4.interpolate(x) - exp(x));
			if (delta > epsilon)
			{
				epsilon = delta;
			}
		}

		data4_un << log(len) << "	" << log(epsilon) << std::endl;

		std::array<double, 4> x_ch = chebyshev_grid<double, 4>(first, first + len);
		std::array<double, 4> y_ch;

		for (unsigned int i = 0; i < 4; i++)
		{
			y_ch[i] = exp(x_ch[i]);
		}

		NewtonInterpolator<double, double, 4> ch_interp4(x_ch, y_ch);
		epsilon = 0;

		for (double x = first; x < len; x += len / s)
		{
			double delta = abs(ch_interp4.interpolate(x) - exp(x));
			if (delta > epsilon)
			{
				epsilon = delta;
			}
		}

		data4_ch << log(len) << "	" << log(epsilon) << std::endl;
	}

	data4_un.close();
	data4_ch.close();


	std::ofstream data5_un("data5_uniform.txt");
	data5_un.precision(15);
	std::ofstream data5_ch("data5_chebyshev.txt");
	data5_ch.precision(15);

	for (double len = step; len < last - first; len += step)
	{
		std::array<double, 5> x_un = uniform_grid<double, 5>(first, first + len);
		std::array<double, 5> y_un;

		for (unsigned int i = 0; i < 5; i++)
		{
			y_un[i] = exp(x_un[i]);
		}

		NewtonInterpolator<double, double, 5> un_interp5(x_un, y_un);
		double epsilon = 0;

		for (double x = first; x < len; x += len / s)
		{
			double delta = abs(un_interp5.interpolate(x) - exp(x));
			if (delta > epsilon)
			{
				epsilon = delta;
			}
		}

		data5_un << log(len) << "	" << log(epsilon) << std::endl;

		std::array<double, 5> x_ch = chebyshev_grid<double, 5>(first, first + len);
		std::array<double, 5> y_ch;

		for (unsigned int i = 0; i < 5; i++)
		{
			y_ch[i] = exp(x_ch[i]);
		}

		NewtonInterpolator<double, double, 5> ch_interp5(x_ch, y_ch);
		epsilon = 0;

		for (double x = first; x < len; x += len / s)
		{
			double delta = abs(ch_interp5.interpolate(x) - exp(x));
			if (delta > epsilon)
			{
				epsilon = delta;
			}
		}

		data5_ch << log(len) << "	" << log(epsilon) << std::endl;
	}

	data5_un.close();
	data5_ch.close();

	return 0;
}

