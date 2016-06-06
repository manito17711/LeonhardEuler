#include "stdafx.h"
#include <iostream>
#include <vector>

using namespace std;

typedef int(*func_ptr) (int n);

int f_tri(int n) { return n * (n + 1) / 2; }
int f_squ(int n) { return n * n; }
int f_pen(int n) { return n * (3 * n - 1) / 2; }
int f_hex(int n) { return n * (2 * n - 1); }
int f_hep(int n) { return n * (5 * n - 3) / 2; }
int f_oct(int n) { return n * (3 * n - 2); }

const vector<func_ptr> functions{ f_tri, f_squ, f_pen, f_hex, f_hep, f_oct };

void find_next_func(vector<func_ptr> functions, int num, vector<int> result);

int main()
{
	int n = 1, m = 0;
	while ((m = functions[0](n++)) < 9999)
	{
		if (m > 1000)
		{
			vector<int> result { m };
			vector<func_ptr> f = functions;
			f.erase(f.begin());

			find_next_func(f, m % 100, result);
		}
	}

	return 0;
}

void find_next_func(vector<func_ptr> func_arr, int num, vector<int> result)
{
	if (result.size() == functions.size())
	{
		if (result[0] / 100 == result[result.size() - 1] % 100)
		{
			int sum = 0;
			for (size_t i = 0; i < result.size(); i++)
			{
				cout << result[i] << " ";
				sum += result[i];
			}

			cout << endl << "Sum: " << sum << endl;
		}
	}
	else
	{
		for (size_t i = 0; i < func_arr.size(); i++)
		{
			int n = 1, m = 0;
			while ((m = func_arr[i](n++)) < 9999)
			{
				if (m > 1000 && (m / 100) == num)
				{
					result.push_back(m);
					vector<func_ptr> f = func_arr;
					f.erase(f.begin() + i);

					find_next_func(f, m % 100, result);
					result.pop_back();
				}
			}
		}
	}
}
