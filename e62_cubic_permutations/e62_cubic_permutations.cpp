// The cube, 41063625 (345^3), can be permuted to produce two other cubes: 56623104 (384^3) and 66430125 (405^3).
// In fact, 41063625 is the smallest cube which has exactly three permutations of its digits which are also cube.
// Find the smallest cube for which exactly five permutations of its digits are cube.

#include <iostream>
#include <stdint.h>
#include <vector>
#include <algorithm>

#define TARGET_PERMUTATIONS 5

uint64_t cube(int);
int count_digits(uint64_t);
bool find_permutations(std::vector<uint64_t>, int);
bool compare_arrays(const int *, const int *, int);
std::vector<int> num_digits(uint64_t);
void split_num_to_digits(uint64_t, int *);

int main()
{
	std::vector<uint64_t> cubes;
	int i = 1, l = 1;
	uint64_t num = 0;

	for (;;)
	{
		cubes.clear();
		for (;;)
		{
			num = cube(i);
			if (count_digits(num) == l)
			{
				cubes.push_back(num);
				i++;
			}
			else
			{
				break;
			}
		}

		if (find_permutations(cubes, l))
		{
			break;
		}
		
		l++;
	}

	std::cout << std::endl;

	return 0;
}

bool find_permutations(std::vector<uint64_t> cubes, int l)
{
	int c, k;

	int * arr_1 = new int[l];
	int * arr_2 = new int[l];

	//int *arr_1 = (int *) malloc(l * sizeof(int));
	//int *arr_2 = (int *) malloc(l * sizeof(int));

	uint64_t t;

	for (size_t i = 0; i < cubes.size() - 1; i++)
	{
		t = cubes[i];
		k = 0;
		c = 1;

		split_num_to_digits(cubes[i], arr_1);
		std::sort(arr_1, arr_1 + l);

		for (size_t j = i + 1; j < cubes.size(); j++)
		{
			split_num_to_digits(cubes[j], arr_2);
			std::sort(arr_2, arr_2 + l);

			if (compare_arrays(arr_1, arr_2, l))
			{
				c++;
				if (c == TARGET_PERMUTATIONS)
				{
					std::cout << cubes[i] << std::endl;
					return true;
				}
			}
		}
	}

	delete[] arr_1;
	delete[] arr_2;

	return false;
}

void split_num_to_digits(uint64_t num, int *arr)
{
	int i = 0;
	while (num > 0)
	{
		arr[i++] = num % 10;
		num /= 10;
	}
}

bool compare_arrays(const int *arr_1, const int *arr_2, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (arr_1[i] != arr_2[i])
		{
			return false;
		}
	}

	return true;
}

std::vector<int> num_digits(uint64_t n)
{
	std::vector<int> v;
	while (n > 0)
	{
		v.push_back(n % 10);
		n /= 10;
	}

	return v;
}

uint64_t cube(int n)
{
	uint64_t r = 1;
	for (size_t i = 0; i < 3; i++)
	{
		r *= n;
	}
	
	return r;
}

int count_digits(uint64_t n)
{
	int c = 1;
	while (n / 10 > 0)
	{
		c++;
		n /= 10;
	}

	return c;
}

