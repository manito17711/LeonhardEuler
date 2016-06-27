// A Pythagorean triplet is a set of three natural numbers, a < b < c, for which a2 + b2 = c2
// For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.
// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
// Find the product abc.
//
// https://www.mathsisfun.com/numbers/pythagorean-triples.html

#include <iostream>

int main()
{
	int m = 1, n = 2;

	bool run = true;
	while (run)
	{
		m = 1;
		while (m < n)
		{
			// The key to the solution is in the link above

			int a = n * n - m * m;
			int b = 2 * n * m;
			int c = n * n + m * m;
			
			if (a + b + c == 1000)
			{
				std::cout << "{" << a << "} {" << b << "} {" << c << "}" << std::endl;
				std::cout << "Product: " << a * b * c << std::endl;
				run = false;
				break;
			}

			m++;
		}

		n++;
	}

	return 0;
}