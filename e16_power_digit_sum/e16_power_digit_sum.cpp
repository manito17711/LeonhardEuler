/*
2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 21000?
*/

#include <iostream>
#include <array>
#include <algorithm>

#define NUM_DIGITS_COUNT 302
//  Assume k=2^1000, then take log on both sides logk=1000 log2 ≈ 301.02999 > 301 log⁡k=1000 log⁡2 ≈ 301.02999 > 301
//  Therefore 2^1000 has 302 digits.

#define MAX_POW 1000

int sum_array_gidits(const std::array<int, NUM_DIGITS_COUNT> & num);
void print_array(const std::array<int, NUM_DIGITS_COUNT> & num);

int main()
{
	std::array<int, NUM_DIGITS_COUNT> num = { 0 };
	num[0] = 2; // 2 POW 1
	int n = 0, m = 0;

	for (int i = 2; i <= MAX_POW; i++)
	{
		for (int j = 0; j < NUM_DIGITS_COUNT; j++)
		{
			m = num[j] * 2 + n;
			n = m / 10;

			num[j] = m % 10;
		}
	}

	std::cout << sum_array_gidits(num) << std::endl;

	return 0;
}

int sum_array_gidits(const std::array<int, NUM_DIGITS_COUNT> & num)
{
	int sum = 0;
	std::for_each(num.begin(), num.end(), [&sum](int x) { sum += x; });

	return sum;
}

void print_array(const std::array<int, NUM_DIGITS_COUNT> & num)
{
	std::for_each(num.begin(), num.end(), [](int x) { std::cout << x; });
}
