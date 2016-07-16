// It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits, but in a different order.
//
// Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.

#include <iostream>
#include <algorithm>

#define L_BOUND 2
#define H_BOUND 6

bool has_same_digits(int, int);
int get_num_length(int);

int main()
{
	int n = 10, n_t = 10;
	int s, t;
	bool flag;

	while (true)
	{
		flag = true;

		for (s = L_BOUND; s <= H_BOUND; s++)
		{
			t = n * s;
			if (get_num_length(n) != get_num_length(t))
			{
				flag = false;
				break;
			}
			else
			{
				if (!has_same_digits(n, t))
				{
					flag = false;
					break;
				}
			}
		}

		if (flag)
		{
			break; // result found
		}

		/*
		16 is the highest value (first two digits from the value) that multiplied by 6 gives a result with same numbers length.

		16 * 6 = 96  - result has the same length
		17 * 6 = 102 - result has more than the multiplicand number length... this is the next length group

		When we've reached to number with first two digits are bigger than 16, we reset the number to the first value
		from next length group..

		Example:
		- n = 17  -> we reset to 100 - first number from next length group
		- n = 170 -> we reset to 1000 and so on..
		*/

		if ((n / n_t) > 16)
		{
			n_t *= 10;
			n = n_t * 10;
		}
		else
		{
			n++;
		}
	}

	for (int i = L_BOUND; i <= H_BOUND; i++)
	{
		std::cout << n << " x " << i << " = " << n * i << std::endl;
	}

	return 0;
}

bool has_same_digits(int n, int t)
{
	int c = get_num_length(n);

	int * arr_1 = new int[c];
	int * arr_2 = new int[c];

	for (int i = 0; i < c; i++)
	{
		arr_1[i] = n % 10;
		n /= 10;

		arr_2[i] = t % 10;
		t /= 10;
	}

	std::sort(arr_1, arr_1 + c);
	std::sort(arr_2, arr_2 + c);

	bool result = true;
	for (int i = 0; i < c; i++)
	{
		if (arr_1[i] != arr_2[i])
		{
			result = false;
		}
	}

	delete[] arr_1;
	delete[] arr_2;

	return result;
}

int get_num_length(int n)
{
	int c = 0;
	while (n > 0)
	{
		c++;
		n /= 10;
	}

	return c;
}
