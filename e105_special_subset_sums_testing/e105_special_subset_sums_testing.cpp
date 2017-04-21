/*
	Let S(A) represent the sum of elements in set A of size n. We shall call it a special sum set if for any two non-empty disjoint subsets,
	B and C, the following properties are true:

	 i. S(B) ≠ S(C); that is, sums of subsets cannot be equal.
	ii. If B contains more elements than C then S(B) > S(C).
	
	For example, {81, 88, 75, 42, 87, 84, 86, 65} is not a special sum set because 65 + 87 + 88 = 75 + 81 + 84,
	whereas {157, 150, 164, 119, 79, 159, 161, 139, 158} satisfies both rules for all possible subset pair combinations and S(A) = 1286.

	Using sets.txt (right click and "Save Link/Target As..."), a 4K text file with one-hundred sets containing seven to twelve elements
	(the two examples given above are the first two sets in the file), identify all the special sum sets, A1, A2, ..., Ak,
	and find the value of S(A1) + S(A2) + ... + S(Ak).


	!!! Compile with Mingw32 - run in 1.5 s.	..MSVC2015-x64 sucks... !!!
*/

#include <iostream>
#include <iterator>
#include <fstream>
#include <sstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <future>
#include <numeric>

#include "next_combination.hpp"

using namespace std;

const string FILE_NAME = "p105_sets.txt";

void read_file(const string&, deque<deque<int>>&);
int sum_valid_subset(const deque<int>&);
bool test_case_one(const deque<int>&, const deque<int>&);   // check  i. S(B) ≠ S(C); that is, sums of subsets cannot be equal.
bool test_case_two(const deque<int>&, const deque<int>&);   // check ii. If B contains more elements than C then S(B) > S(C).



int main()
{
	deque<deque<int>> values;

	read_file(FILE_NAME, values);

	int sumSets = 0;
	deque<future<int>> futures;

	for_each(values.begin(), values.end(), [&futures](deque<int>& d)
	{
		futures.push_back(async(launch::async, sum_valid_subset, d));
	});

	for_each(futures.begin(), futures.end(), [&sumSets](future<int>& f)
	{
		sumSets += f.get();
	});

	cout << sumSets << endl;

	return 0;
}



int sum_valid_subset(const deque<int>& d)
{
	size_t len_idx_A = 1;

	vector<int> idx_A(d.size()), idx_B;
	iota(idx_A.begin(), idx_A.end(), 0);

	deque<int> setA, setB;

	for (; len_idx_A < d.size(); ++len_idx_A)
	{
		do
		{
			// get indexes of setB
			idx_B.clear();
			copy(idx_A.begin() + len_idx_A, idx_A.end(), back_inserter(idx_B));

			for (size_t i = 1; i <= idx_B.size(); ++i)
			{
				do
				{
					// if setA.size() < setB.size()
					if (i > len_idx_A) break;


					// build set A
					setA.clear();
					for_each(idx_A.begin(), idx_A.begin() + len_idx_A, [&d, &setA](int idx)
					{
						setA.push_back(d.at(idx));
					});


					// build setB
					setB.clear();
					for_each(idx_B.begin(), idx_B.begin() + i, [&d, &setB](int idx)
					{
						setB.push_back(d.at(idx));
					});


					// run test...
					if (!test_case_one(setA, setB))
						return 0;

					if (!test_case_two(setA, setB))
						return 0;


				} while (next_combination(idx_B.begin(), idx_B.end(), i));
			}

		} while (next_combination(idx_A.begin(), idx_A.end(), len_idx_A));
	}


	return accumulate(d.begin(), d.end(), 0);
}



void read_file(const string& fileName, deque<deque<int>>& dq)
{
	ifstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		cerr << "Unable to open the source file.\n";
		exit(1);
	}

	stringstream ss;
	string line;
	int num;
	while (getline(file, line))
	{
		dq.push_back(deque<int>());

		ss.clear();
		ss.str(line);

		while (ss >> num)
		{
			dq[dq.size() - 1].push_back(num);
			ss.ignore();
		}
	}

	file.close();
}



// check  i. S(B) ≠ S(C); that is, sums of subsets cannot be equal.
bool test_case_one(const deque<int>& setA, const deque<int>& setB)
{
	int sumSetA = accumulate(setA.begin(), setA.end(), 0);
	int sumSetB = accumulate(setB.begin(), setB.end(), 0);

	return sumSetA != sumSetB;
}



// check ii. If B contains more elements than C then S(B) > S(C).
bool test_case_two(const deque<int>& setA, const deque<int>& setB)
{
	int sumSetA = accumulate(setA.begin(), setA.end(), 0);
	int sumSetB = accumulate(setB.begin(), setB.end(), 0);


	if (setA.size() == setB.size())
		return sumSetA != sumSetB;


	if (setA.size() > setB.size())
		return sumSetA > sumSetB;


	return sumSetB > sumSetA;
}
