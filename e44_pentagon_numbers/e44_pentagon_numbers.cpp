#include <iostream>
#include <map>

using namespace std;

typedef pair<pair<uint64_t, uint64_t>, pair<uint64_t, uint64_t>> win_type;

bool we_have_a_winner(map<uint64_t, uint64_t>& pentaNums, win_type& winner);
uint64_t pentagon(int n);

int main()
{
	const uint64_t MAX_D = 5000; 

	map<uint64_t, uint64_t> pentaNums;
	win_type winner;
	uint64_t p = 1;

	// pre-load first 5000 pentagon numbers
	while (p < MAX_D)
	{
		pentaNums.insert(make_pair(pentagon(p), p));
		++p;
	}


	while (!we_have_a_winner(pentaNums, winner))
	{
		cout << "fuck... need more nums..\n";
		exit(1);		
	}

	cout << winner.first.first << " " << winner.first.second << " Pj\n";
	cout << winner.second.first << " " << winner.second.second << " Pk\n";

	return 0;
}

uint64_t pentagon(int n)
{
	return n * (3 * n - 1) / 2;
}

bool we_have_a_winner(map<uint64_t, uint64_t>& pentaNums, win_type& winner)
{
	int sz = pentaNums.size();
	if (sz < 2)
		return false;

	map<uint64_t, uint64_t>::iterator begin = pentaNums.begin();
	map<uint64_t, uint64_t>::const_iterator end = pentaNums.end();
	map<uint64_t, uint64_t>::iterator next;

	for (; begin != end; ++begin)
	{
		next = begin;
		++next;

		for (; next != end; ++next)
		{
			uint64_t add = (*begin).first + (*next).first;
			uint64_t sub = (*next).first - (*begin).first;

			if (pentaNums.find(add) == end)
				continue;

			if (pentaNums.find(sub) == end)
				continue;

			winner.first = *begin;
			winner.second = *next;

			return true;
		}
	}

	return false;
}