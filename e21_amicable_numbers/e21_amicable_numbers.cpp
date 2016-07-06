//	Let d(n) be defined as the sum of proper divisors of n (numbers less than n which divide evenly into n).
//	If d(a) = b and d(b) = a, where a ≠ b, then a and b are an amicable pair and each of a and b are called amicable numbers.
//
//	For example, the proper divisors of 220 are 1, 2, 4, 5, 10, 11, 20, 22, 44, 55 and 110; therefore d(220) = 284. 
//	The proper divisors of 284 are 1, 2, 4, 71 and 142; so d(284) = 220.
//
//	Evaluate the sum of all the amicable numbers under 10000.

#include <iostream>
#include <set>

#define UPPER_LIMIT 10000

int sum_of_divisors(int i);

int main()
{
	std::set<int> amicable_nums;
	std::set<int>::iterator it;

	int n = UPPER_LIMIT;
	for (int i = 2; i < n; i++)
	{
		int sum = sum_of_divisors(i);
		int candidate = sum_of_divisors(sum);

		if (i == candidate && candidate != sum)
		{
			amicable_nums.insert(i);
			amicable_nums.insert(candidate);			
		}
	}

	int k = 0;
	for (it = amicable_nums.begin(); it != amicable_nums.end(); it++)
	{
		k += *it;
	}

	std::cout << k << std::endl;

	return 0;
}

int sum_of_divisors(int i)
{
	int result = 0;
	for (int j = 1; j < i; j++)
	{
		if (i % j == 0)
		{
			result += j;
		}
	}

	return result;
}