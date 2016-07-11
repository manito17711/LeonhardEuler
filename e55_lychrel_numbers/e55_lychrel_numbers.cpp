// If we take 47, reverse and add, 47 + 74 = 121, which is palindromic.
// 
// Not all numbers produce palindromes so quickly.For example,
// 
// 349 + 943 = 1292,
// 1292 + 2921 = 4213
// 4213 + 3124 = 7337
// 
// That is, 349 took three iterations to arrive at a palindrome.
// 
// Although no one has proved it yet, it is thought that some numbers, like 196, never produce a palindrome.A number that
// never forms a palindrome through the reverse and add process is called a Lychrel number.Due to the theoretical nature
// of these numbers, and for the purpose of this problem, we shall assume that a number is Lychrel until proven otherwise.
// In addition you are given that for every number below ten - thousand, it will either(i) become a palindrome in less
// than fifty iterations, or , (ii)no one, with all the computing power that exists, has managed so far to map it to a
// palindrome.In fact, 10677 is the first number to be shown to require over fifty iterations before producing a palindrome
// : 4668731596684224866951378664 (53 iterations, 28 - digits).
// 
// Surprisingly, there are palindromic numbers that are themselves Lychrel numbers; the first example is 4994.
// 
// How many Lychrel numbers are there below ten - thousand ?
// 
// NOTE : Wording was modified slightly on 24 April 2007 to emphasise the theoretical nature of Lychrel numbers.

#include <iostream>
#include <vector>

#define MAX_ITERATION 50
#define MAX_NUMBER 10000

typedef std::vector<int> V_INT;

int is_palindromic(V_INT);
V_INT set_lytch_candidate(int);
V_INT set_lytch_candidate(V_INT);

void print_vector(V_INT);

int main()
{
	int counter = MAX_NUMBER;
	V_INT num_vec;

	for (int i = 1; i <= MAX_NUMBER; i++)
	{
		num_vec = set_lytch_candidate(i);

		for (int j = 0; j < MAX_ITERATION; j++)
		{
			if (is_palindromic(num_vec))
			{
				if (0) // for debbuging purpose.. manually set to false (0)
				{
					std::cout << "i = " << i;
					std::cout << " / j = " << j + 1;
					std::cout << " / vector = ";
					print_vector(num_vec);
				}

				counter--;
				break;
			}

			num_vec = set_lytch_candidate(num_vec);
		}
	}

	std::cout << "Counter: " << counter << std::endl;
	return 0;
}

V_INT set_lytch_candidate(int n)
{
	V_INT number;
	int n_t = n, i = 0;
	while (n_t > 0)
	{
		n_t /= 10;
		i++;
	}

	for (int j = 0; j < i; j++)
	{
		int d = 1;
		for (int f = j + 1; f < i; f++)
		{
			d *= 10;
		}

		int k = (n / d) % 10;
		number.push_back(k);
	}

	V_INT result = set_lytch_candidate(number);

	return result;
}

V_INT set_lytch_candidate(V_INT number)
{
	V_INT reverced, result;
	for (int i = number.size() - 1; i >= 0; i--)
	{
		reverced.push_back(number.at(i));
	}

	int j = 0;
	for (size_t i = 0; i < number.size(); i++)
	{
		j += number.at(i) + reverced.at(i);
		if (j < 10)
		{
			result.push_back(j);
			j = 0;
			continue;
		}

		result.push_back(j % 10);
		j = 1;
	}

	if (j) result.push_back(j);

	reverced.clear();
	for (int i = result.size() - 1; i >= 0; i--)
	{
		reverced.push_back(result.at(i));
	}

	return reverced;
}

int is_palindromic(V_INT v)
{
	if (v.size() == 1)
	{
		return 1;
	}

	for (int i = 0, j = v.size() - 1; i < v.size() / 2; i++, j--)
	{
		if (v.at(i) != v.at(j))
		{
			return 0;
		}
	}

	return 1;
}

// for debugging...
void print_vector(V_INT v)
{
	for (int i = 0; i < v.size(); i++)
	{
		std::cout << v.at(i);
	}

	std::cout << std::endl;
}