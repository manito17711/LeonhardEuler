/*
	https://projecteuler.net/problem=96

	NOTE: run time ~3 min! Optimizations?!... use C::B
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <set>

using namespace std;

const string FILE_NAME = "p096_sudoku.txt";
const int NINE = 9;

void sudoku_solver(int sudoku[NINE][NINE], int initNums[NINE][NINE]);
void foo(int r, int c, int sudoku[NINE][NINE], int initNums[NINE][NINE]);

bool collisionInRow(int sudoku[NINE][NINE], int row);
bool collisionInCol(int sudoku[NINE][NINE], int col);
bool collisionInBox(int sudoku[NINE][NINE], int row, int col);

int total = 0;
int sudokuCount = 0;

int main()
{
	string token;
	ifstream ss(FILE_NAME);
	while (getline(ss, token)) // Get line with GRID description
	{
		string lineWithDigits;
		int sudoku[NINE][NINE] = { 0 };
		int initNums[NINE][NINE] = { 0 };
		for (int r = 0; r < NINE; ++r)
		{
			getline(ss, lineWithDigits);

			for (int c = 0; c < NINE; ++c)
			{
				sudoku[r][c] = lineWithDigits[c] - 48; // Convert ASCII number to digit
				if (sudoku[r][c] != 0)
				{
					initNums[r][c] = 1;
				}
			}
		}

		try
		{
			sudoku_solver(sudoku, initNums);
		}
		catch (int e)
		{
			if (e == 1)
			{
				// OK.. error for exit from recursion...
			}
			else
			{
				throw e;
			}
		}
	}

	cout << total << endl;

	return 0;
}

void sudoku_solver(int sudoku[NINE][NINE], int initNums[NINE][NINE])
{
	int startRow = 0;
	int startCol = 0;

	foo(startRow, startCol, sudoku, initNums);
}

void foo(int r, int c, int sudoku[NINE][NINE], int initNums[NINE][NINE])
{
	if (r == NINE)
	{
		// solution found
		int firstThreeDigits = sudoku[0][0] * 100 + sudoku[0][1] * 10 + sudoku[0][2];
		total += firstThreeDigits;

		cout << "Grid " << ++sudokuCount << "\t" << firstThreeDigits << endl;
		for (int i = 0; i < NINE; ++i)
		{
			int k = 0;
			cout << "|";
			for (int j = 0; j < NINE; ++j)
			{
				cout << sudoku[i][j];
				if (++k % 3 == 0)
				{
					cout << "|";
				}
			}
			cout << "\n-------------\n";
		}

		// Ugly way to exit from recursion but works...
		throw 1;
	}

	// check for init nums
	if (initNums[r][c] == 1)
	{
		int nextCol = ++c;
		int nextRow = r;
		if (nextCol == NINE)
		{
			nextCol = 0;
			nextRow = ++r;
		}

		foo(nextRow, nextCol, sudoku, initNums);
	}
	else
	{
		for (int i = 1; i <= NINE; ++i)
		{
			sudoku[r][c] = i;

			// check for collisions
			bool hasCollisionInRow = collisionInRow(sudoku, r);
			bool hasCollisionInCol = collisionInCol(sudoku, c);
			bool hasCollisionInBox = collisionInBox(sudoku, r, c);

			// if there are no any collisions, we call foo recursively
			if (!hasCollisionInRow && !hasCollisionInCol && !hasCollisionInBox)
			{
				int nextCol = ++c;
				int nextRow = r;
				if (nextCol == NINE)
				{
					nextCol = 0;
					nextRow = ++r;
				}

				foo(nextRow, nextCol, sudoku, initNums);

				c = nextCol == 0 ? NINE - 1 : --c;
				r = nextCol == 0 ? --r : r;
			}

			// backtracking.. 
			sudoku[r][c] = 0;
		}
	}
}

bool collisionInRow(int sudoku[NINE][NINE], int row)
{
	set<int> nums;
	size_t counter = 0;
	for (int col = 0; col < NINE; ++col)
	{
		int n = sudoku[row][col];
		if (n > 0)
		{
			nums.insert(n);
			++counter;
		}
	}

	bool hasCollision = !(nums.size() == counter);
	return hasCollision;
}

bool collisionInCol(int sudoku[NINE][NINE], int col)
{
	set<int> nums;
	size_t counter = 0;
	for (int row = 0; row < NINE; ++row)
	{
		int n = sudoku[row][col];
		if (n > 0)
		{
			nums.insert(n);
			++counter;
		}
	}

	bool hasCollision = !(nums.size() == counter);
	return hasCollision;
}

bool collisionInBox(int sudoku[NINE][NINE], int row, int col)
{
	int r;
	if (row < 3)
	{
		r = 0;
	}
	else if (row < 6)
	{
		r = 1;
	}
	else
	{
		r = 2;
	}

	int c;
	if (col < 3)
	{
		c = 0;
	}
	else if (col < 6)
	{
		c = 1;
	}
	else
	{
		c = 2;
	}

	int boxRow = r * 3;
	int boxCol = c * 3;

	set<int> nums;
	size_t counter = 0;
	for (int i = boxRow; i < boxRow + 3; ++i)
	{
		for (int j = boxCol; j < boxCol + 3; ++j)
		{
			int n = sudoku[i][j];
			if (n > 0)
			{
				nums.insert(n);
				++counter;
			}
		}
	}

	bool hasCollision = !(nums.size() == counter);
	return hasCollision;
}
