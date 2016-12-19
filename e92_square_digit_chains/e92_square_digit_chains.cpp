/*
	A number chain is created by continuously adding the square of the digits in a number to form a new number until it has been seen before.

	For example,

	44 → 32 → 13 → 10 → 1 → 1
	85 → 89 → 145 → 42 → 20 → 4 → 16 → 37 → 58 → 89

	Therefore any chain that arrives at 1 or 89 will become stuck in an endless loop. What is most amazing is that EVERY
	starting number will eventually arrive at 1 or 89.

	How many starting numbers below ten million will arrive at 89?
*/

#include <iostream>

const uint64_t TEN_MILION = 10000000;

uint64_t next_num(uint64_t n);

int squares[10] = { 0 };
void load_squares(); // pointless optimization

int main()
{
	load_squares();

	uint64_t counter = 0;
	for (uint64_t i = 2; i < TEN_MILION; ++i)
	{
		uint64_t t = 0;
		while (true)
		{
			t = t == 0 ? next_num(i) : next_num(t);

			if (t == 89)
			{
				++counter;
				break;
			}

			if (t == 1)
			{
				break;
			}
		}
	}

	std::cout << counter << std::endl;

	return 0;
}


uint64_t next_num(uint64_t n)
{
	uint64_t t = 0;
	while (n > 0)
	{
		int i = n % 10;
		t += squares[i];
		n /= 10;
	}

	return t;
}

void load_squares()
{
	for (int i = 0; i < 10; ++i)
	{
		squares[i] = i * i;
	}
}
