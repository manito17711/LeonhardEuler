// If p is the perimeter of a right angle triangle with integral length sides, {a,b,c},
//  there are exactly three solutions for p = 120.
//
// {20,48,52}, {24,45,51}, {30,40,50}
//
// For which value of p ≤ 1000, is the number of solutions maximised?


#include <iostream>
#include <math.h>
#include <map>

#define MAX_PERIMETER 1000

double perimeter_right_angle_triangle(int a, int b);

int main()
{
	std::map<double, int> perimeters_and_counters;

	int a = 1, b = 1;
	double p;

	bool is_running = true;
	bool is_b_incremented = false;

	while (is_running)
	{
		p = perimeter_right_angle_triangle(a, b);

		if (p <= MAX_PERIMETER)
		{
			if (perimeters_and_counters.find(p) != perimeters_and_counters.end())
			{
				perimeters_and_counters[p]++;
			}
			else
			{
				perimeters_and_counters[p] = 1;
			}

			b++;
			is_b_incremented = true;
		}
		else if (is_b_incremented)
		{
			a++;
			b = a;
			is_b_incremented = false;
		}
		else
		{
			is_running = false;
		}
	}

	int max_count = 0;
	for (auto it = perimeters_and_counters.begin(); it != perimeters_and_counters.end(); it++)
	{
		if (it->second > max_count)
		{
			p = it->first;
			max_count = it->second;
		}
	}

	std::cout << "Perimeter: " << p << "\tCount: " << max_count << std::endl;

	return 0;
}

double perimeter_right_angle_triangle(int a, int b)
{
	double p = a + b + sqrt(a * a + b * b);

	return  p;
}
