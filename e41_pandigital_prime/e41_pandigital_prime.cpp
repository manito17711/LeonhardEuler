// We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.
//
// What is the largest n - digit pandigital prime that exists ?

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

#define LARGEST_PANDIGITAL_PRIME 987654321
#define DECREMENT_VALUE 500000

std::mutex mtx;

void foo(int h_bound, int l_bound);

int is_prime(int num);
int is_pandigital(int num);

int largest = 0;

int main()
{
	int l_bound = 0, h_bound = 0;
	std::vector<std::thread> threads;

	for (int i = LARGEST_PANDIGITAL_PRIME; i > 0; i -= DECREMENT_VALUE)
	{
		h_bound = i;
		l_bound = (i - DECREMENT_VALUE) > 0 ? (i - DECREMENT_VALUE) : 0;

		threads.push_back(std::thread(foo, h_bound, l_bound));
	}

	for (size_t i = 0; i < threads.size(); i++)
	{
		threads[i].join();
	}

	std::cout << largest << std::endl;

	return 0;
}

void foo(int h_bound, int l_bound)
{
	for (int i = h_bound; i > l_bound; i -= 2)
	{
		if (is_pandigital(i))
		{
			if (is_prime(i))
			{
				mtx.lock();
				if (i > largest)
				{
					largest = i;
				}
				mtx.unlock();
			}
		}
	}
}

int is_pandigital(int num)
{
	int length = 0;
	int f = num;
	while (f > 0)
	{
		length++;
		f /= 10;
	}

	while (num > 0)
	{
		int k = num % 10;
		if (k > length || k == 0)
		{
			return 0;
		}

		num /= 10;
		int t = num;

		while (t > 0)
		{
			int s = t % 10;
			if (s == k)
			{
				return 0;
			}
			t /= 10;
		}
	}

	return 1;
}

int is_prime(int num)
{
	if (num < 2)
	{
		return 0;
	}

	if (num == 2 || num == 3)
	{
		return 1;
	}

	if (num % 2 == 0 || num % 3 == 0)
	{
		return 0;
	}

	int i = 0;
	for (i = 5; i * i <= num; i += 6)
	{
		if (num % i == 0 || num % (i + 2) == 0)
		{
			return 0;
		}
	}

	return 1;
}


