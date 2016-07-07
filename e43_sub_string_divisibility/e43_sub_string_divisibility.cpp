// The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9
// in some order, but it also has a rather interesting sub-string divisibility property.
//
// Let d1 be the 1st digit, d2 be the 2nd digit, and so on.In this way, we note the following :
//
//		d2d3d4 = 406 is divisible by 2
//		d3d4d5 = 063 is divisible by 3
//		d4d5d6 = 635 is divisible by 5
//		d5d6d7 = 357 is divisible by 7
//		d6d7d8 = 572 is divisible by 11
//		d7d8d9 = 728 is divisible by 13
//		d8d9d10 = 289 is divisible by 17
//
// Find the sum of all 0 to 9 pandigital numbers with this property.

#include <iostream>
#include <algorithm>

using namespace std;

long long pow(int, int);
long long get_num(int, const int *, int);

int main()
{
	const int arr_lngth = 3;

	int nums[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	int primes[] = { 1, 2, 3, 5, 7, 11, 13, 17 };
	unsigned long long sum_nums = 0;

	do
	{
		size_t start_index = 1;
		int flag = 1, primes_counter = 1, n, index;
		long long num;
		while ((start_index + arr_lngth) <= (sizeof(nums) / sizeof(nums[0])))
		{
			n = arr_lngth - 1;
			index = start_index;
			num = get_num(n, nums, index);

			if (num % primes[primes_counter] != 0)
			{
				flag = 0;
				break;
			}

			start_index++;
			primes_counter++;
		}

		if (flag)
		{
			n = (sizeof(nums) / sizeof(nums[0]) - 1);
			index = 0;
			num = get_num(n, nums, index);

			cout << num << endl;
			sum_nums += num;
		}

	} while (next_permutation(nums, nums + (sizeof(nums) / sizeof(nums[0]))));


	cout << endl << sum_nums << endl;
	return 0;
}

long long pow(int num, int n)
{
	int res = 1;
	while (n > 0)
	{
		res *= num;
		n--;
	}

	return res;
}

long long get_num(int n, const int * nums, int index)
{
	long long num = 0;
	while (n >= 0)
	{
		num += nums[index] * pow(10, n);
		n--;
		index++;
	}

	return num;
}
