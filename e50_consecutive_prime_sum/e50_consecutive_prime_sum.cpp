// The prime 41, can be written as the sum of six consecutive primes:
// 
// 41 = 2 + 3 + 5 + 7 + 11 + 13
// This is the longest sum of consecutive primes that adds to a prime below one - hundred.
// 
// The longest sum of consecutive primes below one - thousand that adds to a prime, contains 21 terms, and is equal to 953.
// 
// Which prime, below one - million, can be written as the sum of the most consecutive primes ?

#include <iostream>
#include <vector>

#define ONE_MILLION 1000000

int is_prime(int);

int main()
{
	std::vector<int> primes;
	primes.push_back(2); // firts prime
	int n = 3; // second prime

	while (n < ONE_MILLION)
	{
		if (is_prime(n))
		{
			primes.push_back(n);
		}

		n += 2;
	}

	int sum, t_count, r_num, r_count = 0;
	for (size_t i = 0; i < primes.size(); i++)
	{
		sum = primes[i];
		t_count = 1;

		for (size_t j = i + 1; j < primes.size(); j++)
		{
			sum += primes[j];
			if (sum > ONE_MILLION)
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

	std::cout << r_num << std::endl;

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