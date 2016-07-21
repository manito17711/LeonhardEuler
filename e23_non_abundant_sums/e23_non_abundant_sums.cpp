/*
 A perfect number is a number for which the sum of its proper divisors is exactly equal to the number.
 For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28
 is a perfect number.

 A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant
 if this sum exceeds n.

 As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written
 as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers
 greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot
 be reduced any further by analysis even though it is known that the greatest number that cannot be
 expressed as the sum of two abundant numbers is less than this limit.

 Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#include <stdio.h>

#define MAX_LIMIT 28123

int is_abundant(int);
void gen_abundant_nums(void);
void load_ab_nums_by_sum(void);

int N[MAX_LIMIT] = { 0 };
int A[7000] = { 0 }, a_i = 0; // Count of abundant numbers up to 28123.. precalculated value

int main()
{
	gen_abundant_nums();
	load_ab_nums_by_sum();

	int i;
	int sum = 0;
	for (i = 0; i < MAX_LIMIT; i++)
	{
		if (N[i] == 0)
		{
			sum += i;
		}
	}

	printf("%d\n", sum);
	return 0;
}

void load_ab_nums_by_sum(void)
{
	int i, j, num_i, num_j;
	for (i = 0; i < a_i; i++)
	{
		num_i = A[i];
		for (j = i; j < a_i; j++)
		{
			num_j = A[j];
			if (num_i + num_j < MAX_LIMIT)
			{
				N[num_i + num_j] = 1;
			}
		}
	}
}

void gen_abundant_nums(void)
{
	int i;
	for (i = 1; i < MAX_LIMIT; i++)
	{
		if (is_abundant(i))
		{
			A[a_i++] = i;
		}
	}
}

int is_abundant(int n)
{
	int k = 0;
	int i;
	for (i = 1; i <= n / 2; i++)
	{
		if (n % i == 0)
		{
			k += i;
			if (k > n)
			{
				return 1;
			}
		}
	}

	return 0;
}
