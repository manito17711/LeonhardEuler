// The prime 41, can be written as the sum of six consecutive primes:
//
// 41 = 2 + 3 + 5 + 7 + 11 + 13
// This is the longest sum of consecutive primes that adds to a prime below one - hundred.
//
// The longest sum of consecutive primes below one - thousand that adds to a prime, contains 21 terms, and is equal to 953.
//
// Which prime, below one - million, can be written as the sum of the most consecutive primes ?

#include <iostream>

using namespace std;

int is_prime(const int);

int main()
{
	int n = 3, top_n = 1000000, arr_length = 78500, arr_counter = 0;
	int arr[78500] = { 0 };
	arr[arr_counter++] = 2;

	while (n < top_n)
	{
		if (is_prime(n))
		{
			arr[arr_counter++] = n;
		}

		n += 2;
	}

	int sum, t_count, r_num, r_count = 0;
	for (int i = 0; i < arr_length; i++)
	{
		sum = arr[i];
		t_count = 1;

		for (int j = i + 1; j < arr_length; j++)
		{
			if (arr[j] == 0)
			{
				break;
			}

			sum += arr[j];
			if (sum > top_n)
			{
				break;
			}

			if (is_prime(sum))
			{
				if (t_count >= r_count)
				{
					r_num = sum;
					r_count = t_count;
				}
			}

			t_count++;
		}
	}

	cout << "r_num: " << r_num << ", r_count: " << r_count << endl;

	return 0;
}

int is_prime(const int num) 
{
	if (num == 2 || num == 3)
	{
		return 1;
	}

	if (num < 2)
	{
		return 0;
	}

	if (num % 2 == 0 || num % 3 == 0)
	{
		return 0;
	}

	int i;
	for (i = 5; i * i <= num; i += 6)
	{
		if (num % i == 0 || num % (i + 2) == 0)
		{
			return 0;
		}
	}

	return 1;
}

