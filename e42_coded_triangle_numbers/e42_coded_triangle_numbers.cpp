// The nth term of the sequence of triangle numbers is given by, tn = ½n(n+1); so the first ten triangle numbers are:
// 
// 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
// 
// By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value.
// For example, the word value for SKY is 19 + 11 + 25 = 55 = t10.If the word value is a triangle number then we shall call the word a triangle word.
// 
// Using words.txt(right click and 'Save Link/Target As...'), a 16K text file containing nearly two - thousand common English words, how many are triangle words ?

#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 16384
#define SRC_FILE "p042_words.txt"

int count_words(char *);
int proceed_word(const char *);
int is_triangle(size_t);

int main()
{
	FILE * src_file = fopen(SRC_FILE, "r");
	char line[BUFFER_SIZE];

	int c = 0;
	while (!feof(src_file))
	{
		size_t readBytes = fread(line, sizeof(char), BUFFER_SIZE, src_file);
		if (readBytes != BUFFER_SIZE)
		{
			line[readBytes] = '\0';
		}

		c = count_words(line);
	}

	printf("%d\n", c);
	fclose(src_file);
	return 0;
}

int count_words(char * line)
{
	size_t counter = 0;
	size_t char_count = 0;
	while (line[char_count] != '\0')
	{
		line[char_count] = 0;
		char_count++;
		counter += proceed_word(&line[char_count]);

		while (line[char_count] != ',')
		{
			if (line[char_count] == '\0')
			{
				return counter;
			}

			line[char_count] = 0;
			char_count++;
		}

		line[char_count++] = 0;
	}
}

int proceed_word(const char * word)
{
	size_t weight = 0, char_count = 0;
	while (word[char_count] != '"')
	{
		//printf("%c", word[char_count]);
		weight += word[char_count] - 'A' + 1;
		char_count++;
	}

	if (is_triangle(weight))
	{
		return 1;
	}

	return 0;
}

int is_triangle(size_t weight)
{
	size_t triangle = 1;
	size_t diff = 2;

	while (triangle <= weight)
	{
		if (triangle == weight)
		{
			return 1;
		}

		triangle += diff;
		diff++;
	}

	return 0;
}

