// A googol (10100) is a massive number: one followed by one-hundred zeros; 100100 is almost unimaginably large:
// one followed by two-hundred zeros. Despite their size, the sum of the digits in each number is only 1.
//
// Considering natural numbers of the form, ab, where a, b < 100, what is the maximum digital sum ?

// Run it under Code::Blocks, not Visual Studio!!!
// Running time: ~35 seconds

#include <iostream>
#include <deque>

#define LIMIT 100

typedef std::deque<int> Deque_Int;

Deque_Int build_num(int, int);
Deque_Int multiply_deque(Deque_Int, Deque_Int);
Deque_Int sum_deques(Deque_Int, Deque_Int);
int sum_deque_elements(Deque_Int);

void print_vector(Deque_Int); // used inly for debugging

int main()
{
	Deque_Int vect;
	int result = 0, temp_sum = 0;
	int aa, bb;

	for (int a = 1; a < LIMIT; a++)
	{
		for (int b = 1; b < LIMIT; b++)
		{
			vect = build_num(a, b);
			temp_sum = sum_deque_elements(vect);
			if (result < temp_sum)
			{
				result = temp_sum;
				aa = a;
				bb = b;
			}
		}
	}

	std::cout << "Result: " << result << ". A = " << aa << ". B = " << bb << std::endl;

	return 0;
}

Deque_Int build_num(int a, int b)
{
	Deque_Int result, num;
	int temp_a = a, temp_d = 0;
	while (temp_a > 0)
	{
		temp_d = temp_a % 10;
		num.push_front(temp_d);
		result.push_front(temp_d);
		temp_a /= 10;
	}

	for (int i = 1; i < b; i++)
	{
		result = multiply_deque(result, num);
	}

	return result;
}

Deque_Int multiply_deque(Deque_Int v1, Deque_Int v2)
{
	Deque_Int v3, v4, result;

	int t = 0, n = 0;
	for (int i = v1.size() - 1; i >= 0; i--)
	{
		if (v2.at(v2.size() - 1) == 0)
		{
			v3.push_front(0);
			break;
		}

		if (v1.at(i) == 0)
		{
			t = n;
		}
		else
		{
			t = v1.at(i) * (v2.at(v2.size() - 1)) + n;
		}

		if (t < 10)
		{
			v3.push_front(t);
			n = 0;
		}
		else
		{
			v3.push_front(t % 10);
			n = t / 10;
		}
	}

	if (n != 0)
	{
		v3.push_front(n);
		n = 0;
	}

	if (v2.size() > 1)
	{
		v4.push_back(0);

		for (int i = v1.size() - 1; i >= 0; i--)
		{
			t = v1.at(i) * (v2.at(0)) + n;
			if (t < 10)
			{
				v4.push_front(t);
				n = 0;
			}
			else
			{
				v4.push_front(t % 10);
				n = t / 10;
			}
		}

		if (n != 0)
		{
			v4.push_front(n);
			n = 0;
		}
	}
	else
	{
		return v3;
	}

	result = sum_deques(v3, v4);

	return result;
}

Deque_Int sum_deques(Deque_Int v1, Deque_Int v2)
{
	Deque_Int result;
	while (v1.size() < v2.size())
	{
		v1.push_front(0);
	}

	while (v2.size() < v1.size())
	{
		v2.push_front(0);
	}

	int t = 0, n = 0;
	for (int i = v1.size() - 1; i >= 0; i--)
	{
		t = v1.at(i) + v2.at(i) + n;
		if (t < 10)
		{
			result.push_front(t);
			n = 0;
		}
		else
		{
			result.push_front(t % 10);
			n = 1;
		}
	}

	if (n)
	{
		result.push_front(1);
	}

	return result;
}

int sum_deque_elements(Deque_Int input)
{
	int sum = 0;
	for (size_t i = 0; i < input.size(); i++)
	{
		sum += input.at(i);
	}

	return sum;
}

void print_vector(Deque_Int v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		std::cout << v.at(i);
	}

	std::cout << std::endl;
}
