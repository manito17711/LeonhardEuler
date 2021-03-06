﻿// Triangle, pentagonal, and hexagonal numbers are generated by the following formulae:
// 
// Triangle	 		Tn = n(n + 1) / 2	 	1, 3, 6, 10, 15, ...
// Pentagonal	 	Pn = n(3n−1) / 2	 	1, 5, 12, 22, 35, ...
// Hexagonal	 	Hn = n(2n−1)	 		1, 6, 15, 28, 45, ...
// 
// It can be verified that T285 = P165 = H143 = 40755.
// 
// Find the next triangle number that is also pentagonal and hexagonal.

#include <iostream>

using namespace std;

typedef unsigned long long uul;

uul triangular(int);
int has_pentagonal(uul);

int main()
{
	int c = 2;
	int n = 3;
	int is_penta = 0;
	uul value;

	while (c)
	{
		value = triangular(n);
		is_penta = has_pentagonal(value);

		if (is_penta)
		{
			int x = value / n;
			cout << "tr: " << n << " / penta: " << is_penta << " / hexa: " << x << " // value = " << value << endl;
			c--;
		}

		n += 2;
	}

	return 0;
}

uul triangular(int n)
{
	uul k = n;
	uul v = (k * (k + 1)) / 2;

	return v;
}

int has_pentagonal(uul value)
{
	uul v = 0;
	uul n = 1;

	while (v < value)
	{
		v = n * (3 * n - 1) / 2;
		if (v == value)
		{
			return n;
		}	

		n++;
	}

	return 0;
}
