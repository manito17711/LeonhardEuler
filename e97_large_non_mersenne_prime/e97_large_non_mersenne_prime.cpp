
/*
	The first known prime found to exceed one million digits was discovered in 1999, and is a Mersenne prime of the form 26972593−1;
	it contains exactly 2,098,960 digits. Subsequently other Mercenne primes, of the form 2p−1, have been found which contain more digits.

	However, in 2004 there was found a massive non-Mersenne prime which contains 2,357,207 digits: 28433x27830457+1.

	Find the last ten digits of this prime number.
*/

#include <iostream>

const uint64_t TEN_DIGITS = 10000000000;

int main()
{
	uint64_t n = 7830457;
	uint64_t p = 2;
	uint64_t t = 2;

	while (n > 1)
	{
		p *= t;
		p %= TEN_DIGITS;
		--n;
	}

	p *= 28433;
	p += 1;

	std::cout << p % TEN_DIGITS << std::endl;

	return 0;
}
