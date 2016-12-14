/*
	In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom right, by only moving to the right and down,
	is indicated in bold red and is equal to 2427.

		( 131 673 234 103  18 
		  201  96 342 965 150
		  630 803 746 422 111
		  537 699 497 121 956
		  805 732 524  37 331 )

	Find the minimal path sum, in matrix.txt (right click and "Save Link/Target As..."), a 31K text file containing a 80 by 80 matrix,
	from the top left to the bottom right by only moving right and down.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

const std::string FILE_NAME = "p081_matrix.txt";
const int N = 80;

void load_file(int mtx[N][N]);
void bar(int mtx[N][N], int tree[N][N]);

int main()
{
	// declare variables
	int tree[N][N] = {0};
	int mtx[N][N] = {0};	

	// load file
	load_file(mtx);

	// run algorithm
	bar(mtx, tree);

	// print result
	std::cout << tree[N - 1][N - 1] << std::endl;

	return 0;
}

void bar(int mtx[N][N], int tree[N][N])
{
	for (int x = 0; x < N; ++x)
	{
		for (int y = 0; y < N; ++y)
		{
			if (x == 0 && y == 0)
			{
				tree[x][y] = mtx[x][y];
				continue;
			}

			if (x == 0)
			{
				tree[x][y] += (tree[x][y - 1] + mtx[x][y]);
				continue;
			}

			if (y == 0)
			{
				tree[x][y] += (tree[x - 1][y] + mtx[x][y]);
				continue;
			}

			tree[x][y] += (std::min(tree[x - 1][y], tree[x][y - 1]) + mtx[x][y]);
		}
	}
}

void load_file(int mtx[N][N])
{
	const char DELIM = ',';
	int x = 0;
	int y = 0;

	std::ifstream file(FILE_NAME);
	std::string line;

	while (std::getline(file, line))
	{
		y = 0;

		std::stringstream iss(line);
		std::string token;
		int n;

		while (iss >> n)
		{
			mtx[x][y] = n;
			if (iss.peek() == DELIM)
			{
				iss.ignore();
			}

			++y;
		}

		++x;
	}
}
