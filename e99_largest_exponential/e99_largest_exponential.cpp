/*
	Comparing two numbers written in index form like 211 and 37 is not difficult, as any calculator would confirm that 211 = 2048 < 37 = 2187.

	However, confirming that 632382^518061 > 519432^525806 would be much more difficult, as both numbers contain over three million digits.

	Using base_exp.txt (right click and 'Save Link/Target As...'), a 22K text file containing one thousand lines with a base/exponent pair
	on each line, determine which line number has the greatest numerical value.

	NOTE: The first two lines in the file represent the numbers in the example given above.
*/

#include <iostream>
#include <fstream>
#include <math.h>

const std::string FILE_NAME = "p099_base_exp.txt";
const int rows = 1000;
const int cols = 2;

int mtx[rows][cols] = { 0 };

void load_file();

int main()
{
	load_file();

	double max_num = 0.0;
	int row = 0;
	for (int r = 0; r < rows; ++r)
	{
		// log(a^b) = b log(a)
		double next_num = (mtx[r][1] * log(mtx[r][0]));

		if (next_num > max_num)
		{
			max_num = next_num;
			row = r;
		}
	}

	// +1 because we start to count from 0
	std::cout << row + 1 << std::endl;

	return 0;
}

void load_file()
{
	int base = 0;
	int exp = 0;
	int i = 0;

	// replace all ',' with ' ' (space) at input file for easy reading..

	std::ifstream file(FILE_NAME);
	if (file.is_open())
	{
		while (file >> base >> exp)
		{
			mtx[i][0] = base;
			mtx[i][1] = exp;

			++i;
		}

		file.close();
	}
}
