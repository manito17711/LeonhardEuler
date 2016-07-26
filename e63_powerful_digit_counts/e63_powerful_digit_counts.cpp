// The 5-digit number, 16807 = 7^5, is also a fifth power. Similarly, the 9-digit number, 134217728 = 8^9, is a ninth power.
// 
// How many n - digit positive integers exist which are also an nth power ?

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <map>

#define OPTIMIZE_CODE

#define MAX_NUM 100
#define MAX_EXP 100

using namespace std;

typedef shared_ptr<vector<int>> vec_ptr;

vec_ptr custom_pow(int num, int exponent);
vec_ptr multiply_vec(const vec_ptr& multiplicant, const vec_ptr& multiplier);

void print_vec_reverced(const vec_ptr &vec);

map<int, map<int, vec_ptr>> backtrack;

int main()
{
	int counter = 0;
	double n = 1;
	double m = 1;

	for (n = 1; n < MAX_NUM; n++)
	{
		for (m = 1; m < MAX_EXP; m++)
		{
			vec_ptr vec = custom_pow(n, m);
			//print_vec_reverced(vec);

			if (vec->size() == m)
			{
				cout << n << " ^ " << m << endl;
				print_vec_reverced(vec);
				cout << endl;

				counter++;
			}

			#ifdef OPTIMIZE_CODE
			if (vec->size() > m)
			{
				break;
			}
			#endif // OPTIMIZE_CODE
		}
	}

	cout << counter << endl;

	return 0;
}

vec_ptr custom_pow(int num, int exponent)
{
	vec_ptr v1 = vec_ptr(new vector<int>());
	vec_ptr v2 = vec_ptr(new vector<int>());

	int t_n = num;
	while (t_n > 0)
	{
		v1->push_back(t_n % 10);
		v2->push_back(t_n % 10);
		t_n /= 10;
	}

	t_n = 0;
	while (t_n < exponent)
	{
		if (backtrack.find(num) != backtrack.end())
		{
			if (backtrack[num].find(t_n) != backtrack[num].end())
			{
				// vector exists
				v1 = backtrack[num][t_n];
			}
			else
			{
				v1 = multiply_vec(v1, v2);

				pair<int, vec_ptr> t_n_map(t_n, v1);
				backtrack[num].insert(t_n_map);
			}
		}
		else
		{
			pair<int, vec_ptr> t_n_map(t_n, v1);
			pair<int, map<int, vec_ptr>> num_pair;

			num_pair.first = num;
			num_pair.second = map<int, vec_ptr>();
			num_pair.second.insert(t_n_map);

			backtrack.insert(num_pair);
		}

		t_n++;
	}

	return v1;
}

vec_ptr multiply_vec(const vec_ptr& multiplicant, const vec_ptr& multiplier)
{
	vec_ptr result = vec_ptr(new vector<int>());
	vector<vec_ptr> temp_vectors;

	int t = 0, k = 0;
	for (size_t i = 0; i < multiplier->size(); i++)
	{
		temp_vectors.push_back(vec_ptr(new vector<int>()));

		for (size_t j = 0; j < i; ++j)
		{
			temp_vectors[i]->push_back(0);
			temp_vectors[j]->push_back(0);
		}

		k = 0;
		for (size_t multiplicant_index = 0; multiplicant_index < multiplicant->size(); ++multiplicant_index)
		{
			t = multiplier->at(i) * multiplicant->at(multiplicant_index) + k;
			temp_vectors[i]->push_back(t % 10);

			k = t / 10;
		}

		if (k > 0)
		{
			temp_vectors[i]->push_back(k);
		}
	}

	//cout << temp_vectors[0]->size() << endl;
	//cout << temp_vectors[1]->size() << endl;

	size_t max_length = 0;
	for_each(begin(temp_vectors), end(temp_vectors),
		[&max_length](const vec_ptr &v) { max_length < v->size() ? max_length = v->size() : max_length; });

	//cout << max_length << endl;

	int sum = 0;
	for (size_t i = 0; i < max_length; i++)
	{
		for (size_t v_i = 0; v_i < temp_vectors.size(); v_i++)
		{
			if (temp_vectors[v_i]->size() > i)
			{
				sum += temp_vectors[v_i]->at(i);
			}
		}

		result->push_back(sum % 10);
		sum /= 10;
	}

	if (sum > 0)
	{
		result->push_back(sum);
	}

	// remove leading zeros
	for (size_t i = result->size() - 1; i >= 0; i--)
	{
		if (result->at(i) == 0)
		{
			result->pop_back();
		}
		else
		{
			break;
		}
	}

	return result;
}

void print_vec_reverced(const vec_ptr & vec)
{
	for (int i = vec->size() - 1; i >= 0; i--)
	{
		cout << vec->at(i);
	}

	cout << endl;
}