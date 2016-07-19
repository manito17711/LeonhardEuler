// In England the currency is made up of pound, £, and pence, p, and there are eight coins in general circulation:
//
// 1p, 2p, 5p, 10p, 20p, 50p, £1 (100p) and £2 (200p).
//
// It is possible to make £2 in the following way:
// 1×£1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p
//
// How many different ways can £2 be made using any number of coins?

#include <stdio.h>

int main()
{
	const int searched_value = 200;

	// coins values
	int _1p, _2p, _5p, _10p, _20p, _50p, _100p;

	// counter starts from 1 because 200p (2 GBP) is not included at the algorithm.
	int counter = 1;
	int sum;

	for (_100p = 0; _100p <= 2; _100p++)
	{
		for (_50p = 0; _50p <= 4; _50p++)
		{
			for (_20p = 0; _20p <= 10; _20p++)
			{
				for (_10p = 0; _10p <= 20; _10p++)
				{
					for (_5p = 0; _5p <= 40; _5p++)
					{
						for (_2p = 0; _2p <= 100; _2p++)
						{
							for (_1p = 0; _1p <= 200; _1p++)
							{
								sum = (_1p * 1) + (_2p * 2) + (_5p * 5) + (_10p * 10) + (_20p * 20) + (_50p * 50) + (_100p * 100);
								if (sum == searched_value)
								{
									counter++;
								}

								if (sum >= searched_value)
								{
									break;
								}
							}
						}
					}
				}
			}
		}
	}

	printf("%d\n", counter);

	return 0;
}
