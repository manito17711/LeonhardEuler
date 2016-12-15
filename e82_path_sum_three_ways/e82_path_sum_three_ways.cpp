/*
	NOTE: This problem is a more challenging version of Problem 81.

	The minimal path sum in the 5 by 5 matrix below, by starting in any cell in the left column and finishing in any cell
	in the right column, and only moving up, down, and right, is indicated in red and bold; the sum is equal to 994.

		( 131 673 234 103  18 
		  201  96 342 965 150
		  630 803 746 422 111
		  537 699 497 121 956
		  805 732 524  37 331 )
	
	Find the minimal path sum, in matrix.txt (right click and "Save Link/Target As..."), a 31K text file containing a 80 by 80 matrix,
	from the left column to the right column.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

const std::string FILE_NAME = "p082_matrix.txt";
const int N = 80;

void load_file(int mtx[N][N]);
void bar(int mtx[N][N]);
void foo(int mtx[N][N], int tree[N][N], int r, int c);

int min_path = 0;

int main()
{
	// declare variables
	int mtx[N][N] = { 0 };	

	// load file
	load_file(mtx);

	// run algorithm
	bar(mtx);

	// print result
	std::cout << min_path << std::endl;

	return 0;
}

void bar(int mtx[N][N])
{
	for (int n = 0; n < N; ++n)
	{
		int tree[N][N] = { 0 };

		int r = n;
		int next_col = 0;

		tree[r][next_col] = mtx[r][next_col];

		while (next_col + 1 < N)
		{
			int min_v = 0;
			int min_r = r;

			for (int i = 0; i < N; ++i)
			{
				if (tree[i][next_col] == 0)
				{
					continue;
				}

				if (min_v == 0 || min_v > tree[i][next_col])
				{
					min_r = i;
					min_v = tree[i][next_col];
				}
			}

			++next_col;
			foo(mtx, tree, min_r, next_col);
		}

		for (int r = 0; r < N; ++r)
		{
			if (min_path == 0 || min_path > tree[r][N - 1])
			{
				min_path = tree[r][N - 1];
			}
		}
	}
}

void foo(int mtx[N][N], int tree[N][N], int r, int c)
{
	int bkp_r = r;

	tree[r][c] = tree[r][c - 1] + mtx[r][c];

	--r;
	while (r >= 0)
	{
		if (tree[r][c - 1] == 0)
		{
			tree[r][c] = mtx[r][c] + tree[r + 1][c];
		}
		else
		{
			tree[r][c] = mtx[r][c] + (std::min(tree[r + 1][c], tree[r][c - 1]));
		}

		--r;
	}

	r = bkp_r + 1;
	while (r < N)
	{
		if (tree[r][c - 1] == 0)
		{
			tree[r][c] = mtx[r][c] + tree[r - 1][c];
		}
		else
		{
			tree[r][c] = mtx[r][c] + (std::min(tree[r - 1][c], tree[r][c - 1]));
		}

		++r;
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