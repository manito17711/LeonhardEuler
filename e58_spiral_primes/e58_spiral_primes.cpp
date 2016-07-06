//Starting with 1 and spiralling anticlockwise in the following way, a square spiral with side length 7 is formed.
// 
//		37 36 35 34 33 32 31
//		38 17 16 15 14 13 30
//		39 18  5  4  3 12 29
//		40 19  6  1  2 11 28
//		41 20  7  8  9 10 27
//		42 21 22 23 24 25 26
//		43 44 45 46 47 48 49
//
// It is interesting to note that the odd squares lie along the bottom right diagonal, 
// but what is more interesting is that 8 out of the 13 numbers lying along both diagonals are prime;that is, a ratio of 8 / 13 ≈ 62 %.
//
// If one complete new layer is wrapped around the spiral above, a square spiral with side length 9 will be formed.
// If this process is continued, what is the side length of the square spiral for which the ratio of primes along both diagonals 
// first falls below 10 % ?

#include <iostream>
#include <math.h>

#define TARGET_PERCENTAGE 10
#define CUBE_SIZES 4 

bool is_prime(int);
void print_statistics(int, double, double, double);

int main()
{
	int cube_size = 3, num = 0;
	double counter_diagonals = 1, counter_primes = 0, percentage = 0;

	for (;;)
	{
		for (int i = CUBE_SIZES; i >= 1; i--)
		{
			num = (cube_size * cube_size) - ((cube_size - 1) * i);
			counter_diagonals++;

			if (is_prime(num))
			{
				counter_primes++;
			}
		}

		percentage = (counter_primes / counter_diagonals) * 100;

		if (percentage < TARGET_PERCENTAGE)
		{
			break;
		}

		cube_size += 2;
	}

	print_statistics(cube_size, counter_primes, counter_diagonals, percentage);

	return 0;
}

bool is_prime(int num)
{
	if (num < 2)
	{
		return false;
	}

	if (num == 3 || num == 2)
	{
		return true;
	}

	if (num % 2 == 0 || num % 3 == 0)
	{
		return false;
	}

	int i;
	for (i = 5; i * i <= num; i += 6)
	{
		if (num % i == 0 || num % (i + 2) == 0)
		{
			return false;
		}
	}

	return true;
}

void print_statistics(int cube_size, double counter_primes, double counter_diagonals, double percentage)
{
	std::cout << " --- Cube size: ";
	std::cout << cube_size << std::endl;
	std::cout << " --- Primes: ";
	std::cout << counter_primes << std::endl;
	std::cout << " --- Counter diagonals: ";
	std::cout << counter_diagonals << std::endl;
	std::cout << " --- Percentage: ";
	std::cout << percentage << std::endl;
}
