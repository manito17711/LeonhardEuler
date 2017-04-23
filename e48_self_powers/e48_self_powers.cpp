// The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.
// 
// Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.

#include <iostream>

#define LAST_N_DIGITS 10000000000

typedef unsigned long long uul;

uul fact(int);

int main()
{
	uul num = 0;
	int max_pwr = 1000;
	for (int i = 1; i <= max_pwr; i++)
	{
		num += fact(i);
		num %= LAST_N_DIGITS; // we are getting the last N digits from the number and cutting the rest..
	}

	std::cout << num << std::endl;

	return 0;
}

uul fact(int i)
{
	uul f = i;
	for (int j = 1; j < i; j++)
	{
		f *= i;
		f %= LAST_N_DIGITS;
	}

	return f;
}