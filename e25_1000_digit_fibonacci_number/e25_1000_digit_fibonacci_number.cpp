/*
	The Fibonacci sequence is defined by the recurrence relation:

	Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.
	Hence the first 12 terms will be:

	F1 = 1
	F2 = 1
	F3 = 2
	F4 = 3
	F5 = 5
	F6 = 8
	F7 = 13
	F8 = 21
	F9 = 34
	F10 = 55
	F11 = 89
	F12 = 144
	The 12th term, F12, is the first term to contain three digits.

	What is the index of the first term in the Fibonacci sequence to contain 1000 digits?
*/

#include <stdio.h>
#include <string.h>

#define MAX_NUM_DIGITS 1000

void print_num(int*, int);
void gen_next_fib_num(int*, int*, int*);

int main()
{
	int first_num[MAX_NUM_DIGITS] = { 0 };
	int second_num[MAX_NUM_DIGITS] = { 0 };
	int result[MAX_NUM_DIGITS] = { 0 };

	second_num[MAX_NUM_DIGITS - 1] = 1;
	int index = 1;

	while (result[0] < 1)
	{
		gen_next_fib_num(result, first_num, second_num);
		index++;
		//print_num(result, index);

		memcpy(first_num, second_num, MAX_NUM_DIGITS * sizeof(int));
		memcpy(second_num, result, MAX_NUM_DIGITS * sizeof(int));
	}

	print_num(result, index);

	return 0;
}

void gen_next_fib_num(int *result, int *first_num, int *second_num)
{
	int i, d, t = 0;
	for (i = MAX_NUM_DIGITS - 1; i >= 0; i--)
	{
		d = (first_num[i] + second_num[i] + t);
		result[i] = d % 10;

		t = (d >= 10) ? 1 : 0;
	}
}

void print_num(int *num, int index)
{
	int num_length = 0;
	int i = 0;
	while (num[i] == 0)
	{
		printf(" ");
		i++;
	}

	while (i < MAX_NUM_DIGITS)
	{
		printf("%d", num[i]);
		i++;
		num_length++;
	}

	printf("\tIndex: %d, Number length: %d\n", index, num_length);
}