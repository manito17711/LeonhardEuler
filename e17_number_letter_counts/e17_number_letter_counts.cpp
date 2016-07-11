// If the numbers 1 to 5 are written out in words: one, two, three, four, five,
// then there are 3 + 3 + 5 + 4 + 4 = 19 letters used in total.
//
// If all the numbers from 1 to 1000 (one thousand) inclusive were written out in words, how many letters would be used ?
//
// NOTE : Do not count spaces or hyphens.For example, 342 (three hundred and forty - two) contains 23 letters
// and 115 (one hundred and fifteen) contains 20 letters.The use of "and" when writing out numbers is in 
// compliance with British usage.

#include <iostream>
#include <algorithm>
#include <string>

#define ONE_THOUSAND 1000

int count_letters(std::string);

int main()
{
	std::string nums[] =
	{
		"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
		"eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
	};

	std::string decades[] = 
	{
		"", "ten", "twenty ", "thirty ", "forty ", "fifty ", "sixty ", "seventy ", "eighty ", "ninety "
	};

	std::string hundred[] =
	{
		"", "one hundred ", "two hundred ", "three hundred ", "four hundred ", "five hundred ",
		"six hundred ", "seven hundred ", "eight hundred ", "nine hundred "
	};

	std::string name;
	int temp, index, result = 0;
	for (int i = 1; i < ONE_THOUSAND; i++)
	{
		name = "";
		temp = i;
		index = (temp / 100) % 10;
		temp %= 100;
		if (index != 0)
		{
			name += hundred[index];

			if (temp > 0)
			{
				name += " and ";
			}
			else
			{
				result += count_letters(name);
				continue;
			}
		}

		if (temp < 20)
		{
			name += nums[temp];
			result += count_letters(name);
			continue;
		}
		else
		{
			index = (temp / 10) % 10;
			name += decades[index];
		}

		temp %= 10;
		if (temp != 0)
		{
			name += nums[temp];
		}

		result += count_letters(name);
	}

	result += count_letters("one thousand");

	std::cout << result << std::endl;

	return 0;
}

int count_letters(std::string str)
{
	int counter = 0;
	for (size_t i = 0; i < str.length(); i++)
	{
		if (str[i] >= 97 && str[i] <= 122) // Codes by ASCII Table
		{
			counter++;
		}
	}

	return counter;
}