// There are exactly ten ways of selecting three from five, 12345:
//
// 123, 124, 125, 134, 135, 145, 234, 235, 245, and 345
//
// In combinatorics, we use the notation, 5C3 = 10.
//
// In general,
//
// nCr = n!r!(n−r)!, where r ≤ n, n!= n×(n−1)×...×3×2×1, and 0!= 1.
//
// It is not until n = 23, that a value exceeds one - million: 23C10 = 1144066.
// How many, not necessarily distinct, values of  nCr, for 1 ≤ n ≤ 100, are greater than one - million ?


#include <iostream>
#include <vector>

using namespace std;

#define MAX_N 100
#define ONE_MILION 1000000

uint64_t count_combinations(int, int);

int main()
{
	uint64_t counter = 0, combinations = 0;

	for (int n = 1; n <= MAX_N; n++)
	{
		for (int r = 1; r <= n; r++)
		{
			combinations = count_combinations(n, r);

			if (combinations > ONE_MILION)
			{
				counter++;
			}
		}
	}

	cout << counter << endl;
	return 0;
}

uint64_t count_combinations(int n, int r)
{
	vector<int> vec_n, vec_r;
	int n_t = n;
	while (n_t > r)
	{
		vec_n.push_back(n_t);
		n_t--;
	}

	int r_t = n - r;
	while (r_t > 0)
	{
		vec_r.push_back(r_t);
		r_t--;
	}

	for (vector<int>::size_type i_n = 0; i_n != vec_n.size(); i_n++)
	{
		for (vector<int>::size_type i_r = 0; i_r != vec_r.size(); i_r++)
		{
			n_t = vec_n[i_n];
			r_t = vec_r[i_r];

			if (n_t % r_t == 0 && r_t > 1)
			{
				vec_n[i_n] = n_t / r_t;
				vec_r.erase(vec_r.begin() + i_r);

				i_n = -1;
				break;
			}

			if (r_t % n_t == 0 && n_t > 1)
			{
				vec_r[i_r] = r_t / n_t;
				vec_n.erase(vec_n.begin() + i_n);

				i_n = -1;
				break;
			}
		}
	}

	uint64_t n_mtpl = 1;
	for (vector<int>::size_type i_n = 0; i_n != vec_n.size(); i_n++)
	{
		n_mtpl = n_mtpl * vec_n[i_n];
	}

	uint64_t r_mtpl = 1;
	for (vector<int>::size_type i = 0; i != vec_r.size(); i++)
	{
		r_mtpl = r_mtpl * vec_r[i];
	}

	uint64_t result = n_mtpl / r_mtpl;

	return result;
}
