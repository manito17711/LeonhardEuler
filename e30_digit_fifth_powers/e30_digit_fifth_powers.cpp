// Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:
//
// 1634 = 1^4 + 6^4 + 3^4 + 4^4
// 8208 = 8^4 + 2^4 + 0^4 + 8^4
// 9474 = 9^4 + 4^4 + 7^4 + 4^4
//
// As 1 = 1^4 is not a sum it is not included.
//
// The sum of these numbers is 1634 + 8208 + 9474 = 19316.
//
// Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.

#include <stdio.h>
#include <math.h>

#define L_BOUND 10
#define H_BOUND 1000000

int main()
{
	int n, f = 0;
	int i, power = 5;
	for (i = L_BOUND; i < H_BOUND; i++)
	{
		int sum = 0;
		n = i;
		while (n > 0)
		{
			int k = n % 10;
			sum += pow(k, power);
			n /= 10;
		}

		if (sum == i)
		{
			printf("i: %d, sum: %d\n", i, sum);
			f += sum;
		}
	}

	printf("%d\n", f);

	return 0;
}
