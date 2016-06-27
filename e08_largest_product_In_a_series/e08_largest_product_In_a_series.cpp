// The four adjacent digits in the 1000-digit number that have the greatest product are 9 x 9 x 8 x 9 = 5832.
// Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. 
// What is the value of this product?

#include <iostream>
#include <fstream>
#include <string>

#define FILE_NAME "p08_input.txt"
#define N 13

using namespace std;

int main()
{
	ifstream ifstr(FILE_NAME);
	string str;
	if (ifstr.is_open())
	{
		getline(ifstr, str);
		ifstr.close();
	}

	int64_t temp, max = 0;
	for (size_t i = 0; i < str.length() - N; i++)
	{
		temp = 1;
		for (size_t j = i; j < i + N; j++)
		{
			temp *= str[j] - '0';
		}

		max = max < temp ? temp : max;
	}

	cout << max << endl;
	return 0;
}