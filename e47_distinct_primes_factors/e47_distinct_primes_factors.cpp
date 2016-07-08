// The first two consecutive numbers to have two distinct prime factors are:
//
// 14 = 2 × 7
// 15 = 3 × 5
//
// The first three consecutive numbers to have three distinct prime factors are :
// 
// 644 = 2² × 7 × 23
// 645 = 3 × 5 × 43
// 646 = 2 × 17 × 19.
// 
// Find the first four consecutive integers to have four distinct prime factors. What is the first of these numbers ?

// The code runs for about 2 sec on CodeBlocks / MinGW/GCC 
// Under Visual Studio 2015 takes more than 2 minutes.. suppose due to implementation of set but still not sure..


#include <iostream>
#include <set>
#include <vector>

#define FOUR 4

int count_num_factors(int);
int is_prime(int);

std::vector<size_t> primes;
std::set<size_t> factors;

int main()
{
	size_t count_factors, counter = 0, first_of_four = 0, i = 0;
	bool init_first = false;

	while (true)
	{
		i++;

		if (is_prime(i))
		{
			primes.push_back(i);

			init_first = false; // set value to default
			counter = 0; // set value to default
		}
		else
		{
			count_factors = count_num_factors(i);
			if (count_factors != FOUR)
			{
				init_first = false; // set value to default
				counter = 0; // set value to default
				continue;
			}

			if (!init_first)
			{
				first_of_four = i;
				init_first = true;
				counter++;
				continue;
			}

			counter++;
			if (counter == FOUR)
			{
				std::cout << first_of_four << std::endl;
				break;
			}
		}
	}

	return 0;
}

int count_num_factors(int num)
{
	factors.clear();
	for (auto it = primes.begin(); it != primes.end(); it++)
	{
		while (num % 2 == 0)
		{
			factors.insert(2);
			num /= 2;   // give s a new value, otherwise you would go on for a long time.
		}

		size_t current_prime = *it;
		while (num % current_prime == 0)
		{
			factors.insert(current_prime);
			num = num / current_prime;   // give s a new value...
		}

		if (num == 1)
		{
			break;
		}
	}

	return factors.size();
}


int is_prime(int num)
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
