// The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes and concatenating them in any order
// the result will always be prime. For example, taking 7 and 109, both 7109 and 1097 are prime.
// The sum of these four primes, 792,represents the lowest sum for a set of four primes with this property.
//
// Find the lowest sum for a set of five primes for which any two primes concatenate to produce another prime.

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <exception>

#define COUNT_PRIMES 1200
#define COUNT_INDEXES 5

using namespace std;

bool is_prime(int);
void find_prime_pair_sets(int, int, vector<int>);
bool are_current_indexes_valid(vector<int>, int);
void print_result(vector<int>);

vector<int> arr;

int main()
{
	arr.push_back(2);
	arr.push_back(3);
	for (size_t i = 1; i < COUNT_PRIMES; i++)
	{
		int k = arr.at(i) + 2;
		while (!is_prime(k))
		{
			k += 2;
		}

		arr.push_back(k);
	}

	vector<int> indexes;
	for (size_t i = 0; i < COUNT_INDEXES; i++)
	{
		indexes.push_back(i);
	}

	try
	{
		find_prime_pair_sets(0, 0, indexes);
	}
	catch (int e)
	{
		if (!(e == 1))
		{
			throw;
		}
	}

	return 0;
}

void find_prime_pair_sets(int index, int j, vector<int> indexes)
{
	if (index == COUNT_INDEXES)
	{
		print_result(indexes);
		throw 1;
	}
	else
	{
		for (int i = j; i < COUNT_PRIMES; i++)
		{
			indexes[index] = i;
			if (index != 0)
			{
				if (are_current_indexes_valid(indexes, index))
				{
					find_prime_pair_sets(index + 1, i + 1, indexes);

				}
			}
			else
			{
				find_prime_pair_sets(index + 1, i + 1, indexes);
			}
		}
	}
}

bool are_current_indexes_valid(vector<int> indexes, int index)
{
	for (int i = 0; i < index; i++)
	{
		for (int j = i + 1; j <= index; j++)
		{
			string concat_f = to_string(arr[indexes[i]]) + to_string(arr[indexes[j]]);
			int f = stoi(concat_f);
			if (!is_prime(f))
			{
				return false;
			}

			string concat_r = to_string(arr[indexes[j]]) + to_string(arr[indexes[i]]);
			int r = stoi(concat_r);
			if (!is_prime(r))
			{
				return false;
			}
		}
	}
	
	return true;
}

void print_result(vector<int> indexes)
{	
	int sum = 0;
	for (size_t i = 0; i < COUNT_INDEXES; i++)
	{
		cout << arr.at(indexes[i]) << " ";
		sum += arr.at(indexes[i]);
	}

	cout << "\nSum: " << sum << endl;
}

bool is_prime(int num)
{
	if (num < 2)
	{
		return false;
	}

	if (num == 2 || num == 3)
	{
		return true;
	}

	if (num % 2 == 0 || num % 3 == 0)
	{
		return false;
	}

	int i = 0;
	for (i = 5; i * i <= num; i += 6)
	{
		if (num % i == 0 || num % (i + 2) == 0)
		{
			return false;
		}
	}

	return true;
}


