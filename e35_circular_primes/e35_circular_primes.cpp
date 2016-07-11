// The number, 197, is called a circular prime because all rotations of the digits: 197, 971, and 719, are themselves prime.
//
// There are thirteen such primes below 100: 2, 3, 5, 7, 11, 13, 17, 31, 37, 71, 73, 79, and 97.
// 
// How many circular primes are there below one million ?

#include <stdio.h>
#include <math.h>

#define ONE_MILLION 1000000

int is_prime(int);
int is_circular_prime(int);

int main()
{
	int i, counter_circular_primes = 0;
	for (i = 2; i < ONE_MILLION; i++)
	{
		if (is_prime(i))
		{
			if (is_circular_prime(i))
			{
				counter_circular_primes++;
			}
		}
	}

	printf("%d\n", counter_circular_primes);

	return 0;
}

int is_prime(int num)
{
	if (num < 2)
	{
		return 0;
	}

	if (num == 3 || num == 2)
	{
		return 1;
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

int is_circular_prime(int n)
{
	int n_length = 0, t = n;
	while (t > 0)
	{
		n_length++;
		t /= 10;
	}

	t = n;
	int i, k;
	for (i = 0; i < n_length; i++)
	{
		k = t % 10;
		t /= 10;
		t += k * pow(10, n_length - 1);

		if (!is_prime(t))
		{
			return 0;
		}
	}

	return 1;
}