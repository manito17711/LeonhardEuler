// The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases by 3330, is unusual in two ways:
// (i) each of the three terms are prime
// (ii) each of the 4-digit numbers are permutations of one another.
//
// There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes, exhibiting this property,
// but there is one other 4-digit increasing sequence.
//
// What 12-digit number do you form by concatenating the three terms in this sequence?

#include <iostream>
#include <algorithm>

#define INCREASE_VALUE 3330
#define INIT_NUM 1001 // first odd four digit number (possible prime)
#define HIGTH_NUM 6669 // higher possible num.. 9999 - 3330 (INCREASE_VALUE)

bool is_prime(int);
bool is_permutation(const int*);

int main()
{
	int next_num;
	int num = INIT_NUM;
	int t_arr[2];
	bool flag;

	while (num < HIGTH_NUM)
	{
		t_arr[0] = num;

		if (is_prime(num))
		{
			flag = true;
			next_num = num;
			for (int i = 0; i < 2; i++)
			{
				next_num += INCREASE_VALUE;
				t_arr[1] = next_num;
				if (!is_prime(next_num) || !is_permutation(t_arr))
				{
					flag = false;
					break;
				}
			}

			if (flag) // sequence found
			{
				std::cout << num << " / ";
				std::cout << num + INCREASE_VALUE << " / ";
				std::cout << num + INCREASE_VALUE * 2 << std::endl;
			}
		}

		num += 2;
	}

	return 0;
}

bool is_permutation(const int *nums)
{
	const int rows = 2, cols = 4;
	int arr[rows][cols];
	int t_num;

	for (int i = 0; i < rows; i++)
	{
		t_num = *(nums + i);

		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = t_num % 10;
			t_num /= 10;
		}
	}

	std::sort(arr[0], arr[0] + cols);
	std::sort(arr[1], arr[1] + cols);

	for (int i = 0; i < cols; i++)
	{
		if (arr[0][i] != arr[1][i])
		{
			return false;
		}
	}

	return true;
}

bool is_prime(int num)
{
	if (num < 2)
	{
		return false;
	}

	if (num == 3 || num == 2)
	{
		return true;
	}

	if (num % 2 == 0 || num % 3 == 0)
	{
		return false;
	}

	int i;
	for (i = 5; i * i <= num; i += 6)
	{
		if (num % i == 0 || num % (i + 2) == 0)
		{
			return false;
		}
	}

	return true;
}
