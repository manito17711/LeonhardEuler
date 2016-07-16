// It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.
//
// 9 = 7 + 2x1^2
// 15 = 7 + 2x2^2
// 21 = 3 + 2x3^2
// 25 = 7 + 2x3^2
// 27 = 19 + 2x2^2
// 33 = 31 + 2x1^2
//
// It turns out that the conjecture was false.
//
// What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?

#include <iostream>

int is_prime(int);
int next_prime(int);

int main()
{
	int n = 9; // first negative non prime number
	int candidate_for_result = 0, result_found = 0;

	while (1)
	{
		if (!is_prime(n))
		{
			for (int i = next_prime(1); i < n; i = next_prime(i))
			{
				for (int k = 1; k < n; k++)
				{
					result_found = 0;
					candidate_for_result = i + 2 * (k * k);
					if (candidate_for_result > n)
					{
						break;
					}

					if (candidate_for_result == n)
					{
						//cout << n << " = " << i << " + 2x" << k << "^2" << endl;
						result_found = 1;
						break;
					}
				}

				if (result_found)
				{
					break;
				}
			}
		}

		if (result_found)
		{
			n += 2;
		}
		else
		{
			break;
		}
	}

	std::cout << n << std::endl;

	return 0;
}

int next_prime(int num)
{
	int n = num + 2; // next possible prime number
	while (1)
	{
		if (is_prime(n))
		{
			return n;
		}

		n += 2;
	}
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
