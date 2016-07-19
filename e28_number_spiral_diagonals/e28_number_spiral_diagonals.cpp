// Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:
//
//  21 22 23 24 25
//  20  7  8  9 10
//  19  6  1  2 11
//  18  5  4  3 12
//  17 16 15 14 13
//
// It can be verified that the sum of the numbers on the diagonals is 101.
//
// What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?

#include <stdio.h>
#include <stdlib.h>

#define N 1001

int main()
{
	int **matrix = (int**)malloc(N * sizeof(int*));
	int k;
	for (k = 0; k < N; k++)
	{
		matrix[k] = (int*)malloc(N * sizeof(int));
	}

	int num = 1;
	int r = N / 2, c = N / 2;

	matrix[r][c] = num++;
	int t_c = 0, m_c, out = 0;
	while (1)
	{
		t_c++;
		m_c = 0;
		while (m_c < t_c)
		{
			matrix[r][++c] = num++;
			if (num - 1 == N * N)
			{
				out = 1;
				break;
			}

			m_c++;
		}

		if (out == 1)
		{
			break;
		}

		m_c = 0;
		while (m_c < t_c)
		{
			matrix[++r][c] = num++;
			if (num - 1 == N * N)
			{
				out = 1;
				break;
			}

			m_c++;
		}

		if (out == 1)
		{
			break;
		}

		t_c++;
		m_c = 0;
		while (m_c < t_c)
		{
			matrix[r][--c] = num++;
			if (num - 1 == N * N)
			{
				out = 1;
				break;
			}

			m_c++;
		}

		if (out == 1)
		{
			break;
		}

		m_c = 0;
		while (m_c < t_c)
		{
			matrix[--r][c] = num++;
			if (num - 1 == N * N)
			{
				out = 1;
				break;
			}

			m_c++;
		}

		if (out == 1)
		{
			break;
		}
	}

	int i;
	long long sum = 0;
	for (i = 0; i < N; i++)
	{
		sum += matrix[i][i];
		sum += matrix[i][N - i - 1];
	}

	sum--;
	printf("%lld\n", sum);

	for (k = 0; k < N; k++)
	{
		free(matrix[k]);
	}

	free(matrix);

	return 0;
}