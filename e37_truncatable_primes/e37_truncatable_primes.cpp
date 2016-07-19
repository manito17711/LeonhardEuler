// The number 3797 has an interesting property. Being prime itself, it is possible to continuously remove digits from left to right,
// and remain prime at each stage: 3797, 797, 97, and 7. Similarly we can work from right to left: 3797, 379, 37, and 3.
//
// Find the sum of the only eleven primes that are both truncatable from left to right and right to left.
//
// NOTE: 2, 3, 5, and 7 are not considered to be truncatable primes.

#include <iostream>
#include <math.h>

#define TOTAL_TRUNCABLE_PRIMES 11

bool is_prime(int);
bool is_left_truncable(int);
bool is_right_truncable(int);
int get_num_length(int, int);

int main()
{
	int k = 0, sum_primes = 0, num = 9;

	while (k < TOTAL_TRUNCABLE_PRIMES)
	{
		if (is_prime(num))
		{
			if (is_left_truncable(num) && is_right_truncable(num))
			{
				printf("Truncatable prime: %d\n", num);
				sum_primes += num;
				k++;
			}
		}

		num += 2;
	}

	printf("\nTotal: %d\n", sum_primes);
	return 0;
}

bool is_left_truncable(int n)
{
	n /= 10;
	while (n > 0)
	{
		if (!is_prime(n))
		{
			return false;
		}

		n /= 10;
	}

	return true;
}

bool is_right_truncable(int n)
{
	int num_length = get_num_length(n, 10);
	int denominator;
	while (n > 0)
	{
		denominator = pow(10, num_length - 1);
		num_length--;
		n %= denominator;
		if (!is_prime(n) && n > 0)
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

int get_num_length(int n, int base)
{
	int t = n, n_length = 0;
	while (t > 0)
	{
		n_length++;
		t /= base;
	}

	return n_length;
}
