// The decimal number, 585 = 10010010012 (binary), is palindromic in both bases.
//
// Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.
//
// (Please note that the palindromic number, in either base, may not include leading zeros.)


#include <stdio.h>
#include <stdlib.h>

#define ONE_MILLION 1000000

int is_pallindrome_by_base(int, int);
int get_num_length(int, int);

int main()
{
	int i, sum = 0;
	for (i = 1; i < ONE_MILLION; i++)
	{
		int base_10 = is_pallindrome_by_base(i, 10);
		int base_2 = is_pallindrome_by_base(i, 2);

		if (base_10 && base_2)
		{
			//printf("%d\n", i);
			sum += i;
		}
	}

	printf("%d\n", sum);
	return 0;
}

int is_pallindrome_by_base(int n, int base)
{
	int arr_length = get_num_length(n, base);

	int * arr_num = (int *)calloc(arr_length, sizeof(int));
	int * arr_rev = (int *)calloc(arr_length, sizeof(int));

	int i_n, i_r, t = n;
	for (i_n = 0, i_r = arr_length - 1; i_n < arr_length; i_n++, i_r--)
	{
		int k = t % base;
		t /= base;
		arr_num[i_n] = k;
		arr_rev[i_r] = k;
	}

	int i, result = 1;
	for (i = 0; i < arr_length; i++)
	{
		if (arr_num[i] != arr_rev[i])
		{
			result = 0;
			break;
		}
	}

	delete arr_num;
	delete arr_rev;

	return result;
}

int get_num_length(int n, int base)
{
	int t = n, n_length = 0;
	while (t > 0)
	{
		n_length++;
		t /= base;
	}

	return n_length;
}


