//An irrational decimal fraction is created by concatenating the positive integers:
//
// 0.12345678910 "1" 112131415161718192021...
//
// It can be seen that the 12th digit of the fractional part is 1.
//
// If dn represents the nth digit of the fractional part, find the value of the following expression.
//
// d1 x d10 x d100 x d1000 x d10000 x d100000 x d1000000

#include <iostream>

int num_length(int num);

int main()
{
	int total_counter = 0;
	int n = 0;
	int digit;
	int current_num_length;

	int searched_position = 1;
	int searched_positions_counter = 6;

	int result = 1;

	bool is_running = true;
	while (is_running)
	{
		n++;
		current_num_length = num_length(n);

		if (searched_position <= (total_counter + current_num_length) && searched_position > total_counter)
		{
			total_counter += current_num_length;

			int k = 1, f = total_counter - searched_position;
			while (f)
			{
				k *= 10;
				f--;
			}

			digit = n / k % 10;
			result *= digit;

			std::cout << n << "\t" << total_counter << "\t" << searched_position << "\t" << digit << std::endl;

			if (searched_positions_counter > 0)
			{
				searched_position *= 10;
				searched_positions_counter--;
			}
			else
			{
				is_running = false;
			}
		}
		else
		{
			total_counter += current_num_length;
		}
	}

	std::cout << "\nresult: " << result << std::endl;

	return 0;
}

int num_length(int num)
{
	int total_counter = 0;
	while (num > 0)
	{
		total_counter++;
		num /= 10;
	}

	return total_counter;
}
