// Euler discovered the remarkable quadratic formula:
//
// n² + n + 41
//
// It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. However,
//  when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.
//
// The incredible formula  n² − 79n + 1601 was discovered, which produces 80 primes for the consecutive
//  values n = 0 to 79. The product of the coefficients, −79 and 1601, is −126479.
//
// Considering quadratics of the form:
//
// n² + an + b, where |a| < 1000 and |b| < 1000
//
// where |n| is the modulus/absolute value of n
// e.g. |11| = 11 and |−4| = 4
// Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes
//  for consecutive values of n, starting with n = 0.

#include <stdio.h>
#include <stdlib.h>

int max_counter = 0;

int is_prime(int);

int main()
{
	int aMax = 0;
	int bMax = 0;
	int cMax = 0;

	// n^2 + an + b, where |a| < 1000 and |b| < 1000
	const int min_value = -1000;
	const int max_value = 1000;

	int a, b;
	for (a = min_value; a < max_value; a++)
	{
		for (b = min_value; b < max_value; b++)
		{
			int n = 0;
			int num = n * n + n * a + b;
			if (num < 0)
			{
				num *= -1;
			}

			while (is_prime(num))
			{
				n++;
				num = n * n + n * a + b;
				if (num < 0)
				{
					num *= -1;
				}
			}

			if (n > cMax)
			{
				aMax = a;
				bMax = b;
				cMax = n - 1;
			}
		}
	}

	fprintf(stdout, "a: %d, b: %d, c: %d\n", aMax, bMax, cMax);
	fprintf(stdout, "%d\n", aMax * bMax);

	return 0;
}

int is_prime(int num)
{
	if (num < 2)
	{
		return 0;
	}

	if (num == 2 || num == 3)
	{
		return 1;
	}

	if (num % 2 == 0 || num % 3 == 0)
	{
		return 0;
	}

	int i = 0;
	for (i = 5; i * i <= num; i += 6)
	{
		if (num % i == 0 || num % (i + 2) == 0)
		{
			return 0;
		}
	}

	return 1;
}
