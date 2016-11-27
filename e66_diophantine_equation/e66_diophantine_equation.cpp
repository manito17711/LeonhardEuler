/*
	Consider quadratic Diophantine equations of the form:

	x^2 - Dy^2 = 1

	For example, when D=13, the minimal solution in x is 649^2 - 13x180^2 = 1.

	It can be assumed that there are no solutions in positive integers when D is square.

	By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the following:

	3^2 - 2x2^2 = 1
	2^2 - 3x1^2 = 1
	9^2 - 5x4^2 = 1
	5^2 - 6x2^2 = 1
	8^2 - 7x3^2 = 1

	Hence, by considering minimal solutions in x for D ≤ 7, the largest x is obtained when D=5.

	Find the value of D ≤ 1000 in minimal solutions of x for which the largest value of x is obtained.

	-------------------------------------------------------------------------------------------------------------

	The algorithm works!

	Brute force approach with multi threading - spawn threads equal to the processor cores! It will force your CPU to 100%.

!!!	Because task require's operation with big numbers, the "GMP" lib is used. Build and Run under Code::Blocks !!!
	
	Unfortunately it cannot produce result, due to conventional computer does not have enough power to compute... it stuck with MAX_D >= 200 and i5-6200
	There must be some kind of mathematical relationship between x and y with increasing of D value..
*/


#include <gmp.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <limits>
#include <thread>
#include <mutex>
#include <vector>

//#define DEBUG

static std::mutex cout_mutex;
static std::mutex D_mutex;
static std::mutex mtx_Ch;

typedef unsigned long long int ulli;

const int MAX_D = 15; // Low MAX_D value in order to check algorithm running flow.

void PerformCalc();
void CheckHighiestX(mpz_t x, int d);
void DebugPrint(mpz_t x, mpz_t y, int d, std::thread::id id);

mpz_t out_X;
int out_D;

int D = 2;

int main()
{
	out_D = 0;
	mpz_init_set_ui(out_X, out_D);

	// get processors count
	std::vector<std::thread> threads;
	auto nthreads = std::thread::hardware_concurrency();

	// spawn threads..
	for (size_t i = 0; i < nthreads; ++i)
	{
		threads.push_back(std::thread(PerformCalc));
	}

	// join threads
	for (auto &t : threads)
	{
		static int l = 0;
		t.join();
		std::cout << "Thread join " << l++ << std::endl;
	}

	// print result
	std::cout << "X = ";
	mpz_out_str(stdout, 10, out_X);
	std::cout << "\nD = " << out_D << std::endl;

	mpz_clear(out_X);

	return 0;
}

void PerformCalc()
{
	int d;

	while (true)
	{
		{
			std::lock_guard<std::mutex> lock(D_mutex);
			d = D;
			++D;
		}

		if (d >= MAX_D) return;

		// It can be assumed that there are no solutions in positive integers when D is square.
		// checking if D is square..
		auto sqrD = sqrt(d);
		if (floor(sqrD) != sqrD)
		{
			mpz_t x, y, y_i;
			mpz_init(x);
			mpz_init(y);
			mpz_init_set_ui(y_i, 1);

			while (true)
			{
				// calculating the right side of the equation
				mpz_set(y, y_i);
				mpz_mul(y, y, y);
				mpz_mul_ui(y, y, d);
				mpz_add_ui(y, y, 1);

				// calculating the left side of the equation
				mpz_sqrt(x, y);
				mpz_mul(x, x, x);

				// comparing.. if the result is 0 then we've got a solution
				if (mpz_cmp(x, y) == 0)
				{
					mpz_sqrt(x, x);
					CheckHighiestX(x, d);

#ifdef DEBUG

					mpz_sub_ui(y, y, 1);
					mpz_div_ui(y, y, d);
					mpz_sqrt(y, y);

					std::thread::id id = std::this_thread::get_id();
					DebugPrint(x, y, d, id);

#endif // DEBUG

					break;
				}
				else
				{
					mpz_add_ui(y_i, y_i, 1);
				}
			}

			mpz_clear(x);
			mpz_clear(y);
		}
	}
}

void CheckHighiestX(mpz_t x, int d)
{
	std::lock_guard<std::mutex> lock(mtx_Ch);

	if (mpz_cmp(out_X, x) <= 0)
	{
		mpz_set(out_X, x);
		out_D = d;
	}
}

void DebugPrint(mpz_t x, mpz_t y, int d, std::thread::id id)
{
	std::lock_guard<std::mutex> lock(cout_mutex);

	std::cout << "x = ";
	mpz_out_str(stdout, 10, x);
	std::cout << " D = " << d;
	std::cout << " y = ";
	mpz_out_str(stdout, 10, y);
	std::cout << " Thread ID: " << id << std::endl;
}
