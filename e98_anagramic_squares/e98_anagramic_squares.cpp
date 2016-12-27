/*
	By replacing each of the letters in the word CARE with 1, 2, 9, and 6 respectively, we form a square number: 1296 = 36^2.
	What is remarkable is that, by using the same digital substitutions, the anagram, RACE, also forms a square number: 9216 = 96^2.
	We shall call CARE (and RACE) a square anagram word pair and specify further that leading zeroes are not permitted,
	neither may a different letter have the same digital value as another letter.

	Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words,
	find all the square anagram word pairs (a palindromic word is NOT considered to be an anagram of itself).

	What is the largest square number formed by any member of such a pair?

	NOTE: All anagrams formed must be contained in the given text file.

	Code::Blocks - run time for less than 3 sec!
	Visual Studio - run time ~50 sec.. you should use C::B..
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <math.h>

const std::string FILE_NAME = "p098_words.txt";

struct Node
{
	std::string word;
	std::string revWord;
	std::string wordStamp;
	uint64_t currentMapSquare;
	int currentMapSquareIndex;
	bool isMapSquareInit;
	std::map<char, int> mapCharsDigits;

	Node() {}
	Node(const Node &cpyObj);
	Node(const std::string &word);

	void buildStamp();
	void resetMap();
};

struct Result
{
	uint64_t square;
	Node a;
} Result;

std::unordered_map<uint64_t, int> squaresRev; // pre-calculated data - squaresReverse from 1 to 10 ^ 10
std::unordered_map<int, uint64_t> squares; // pre-calculated data - squares from 1 to 10 ^ 10
void load_precalculated_squares();

std::unordered_map<int, uint64_t> pows; // pre-calculated data - pows 10 ^ (1 - 10)
void load_precalculated_pows();


void run_main_algorithm(std::vector<Node> &vec);
void del_useless_words(std::vector<Node> &vec);
void foo(Node a, Node b);
bool set_next_possible_sqaure(Node &a);
bool check_set_if_square(std::map<char, int> mapCharsDigits, Node &b);
bool is_square_has_unique_digits(uint64_t sq);

int main()
{
	load_precalculated_pows();
	load_precalculated_squares();

	std::ifstream file(FILE_NAME);
	std::string word;
	std::vector<Node> wordsVect;
	if (file.is_open())
	{
		while (std::getline(file, word, ','))
		{
			wordsVect.emplace_back(word.substr(1, word.length() - 2));
		}

		file.close();
	}

	std::sort(wordsVect.begin(), wordsVect.end(),
		[](Node a, Node b)
	{
		return a.wordStamp < b.wordStamp;
	});

	del_useless_words(wordsVect); // words without anagrams
	run_main_algorithm(wordsVect);

	std::cout << "Result obj->square:\t" << Result.square << std::endl;
	std::cout << "Result obj->word:\t" << Result.a.word << std::endl;

	return 0;
}

void run_main_algorithm(std::vector<Node> &vec)
{
	for (size_t i = 0; i < vec.size(); ++i)
	{
		Node a = vec[i];
		Node b;

		for (size_t j = i + 1; j < vec.size(); ++j)
		{
			b = vec[j];

			if (a.wordStamp.compare(b.wordStamp) == 0)
			{
				foo(a, b);
			}
		}
	}
}

void foo(Node a, Node b)
{
	while (set_next_possible_sqaure(a))
	{
		std::map<char, int> possibleMap = a.mapCharsDigits;

		if (check_set_if_square(possibleMap, b))
		{
			if (a.currentMapSquare > Result.square)
			{
				Result.square = a.currentMapSquare;
				Result.a = a;
			}

			if (b.currentMapSquare > Result.square)
			{
				Result.square = b.currentMapSquare;
				Result.a = b;
			}
		}
	}

	a.resetMap();
	b.resetMap();
}

bool check_set_if_square(std::map<char, int> mapCharsDigits, Node &b)
{
	uint64_t num = 0;

	for (size_t i = 0; i < b.word.size(); ++i)
	{
		char c = b.word[i];
		int d = mapCharsDigits[c];
		int n = b.word.size() - 1 - i;

		num += (d * pows[n]);
	}

	if (num < pows[b.word.size() - 1])
	{
		return false;
	}

	if (squaresRev.find(num) != squaresRev.end())
	{
		b.currentMapSquare = num;
		b.currentMapSquareIndex = squaresRev[num];
		return true;
	}

	return false;
}

bool set_next_possible_sqaure(Node &a)
{
	if (!a.isMapSquareInit)
	{
		a.isMapSquareInit = true;
	}
	else if (squares[a.currentMapSquareIndex + 1] <= pows[a.word.length()])
	{
		++a.currentMapSquareIndex;
		a.currentMapSquare = squares[a.currentMapSquareIndex];
	}
	else
	{
		return false;
	}

	auto tempNum = a.currentMapSquare;
	a.mapCharsDigits.clear();
	for (size_t i = 0; i < a.revWord.size(); ++i)
	{
		char c = a.revWord[i];
		int d = tempNum % 10;
		tempNum /= 10;
		a.mapCharsDigits[c] = d;
	}

	return true;
}

void del_useless_words(std::vector<Node> &vec)
{
	std::vector<size_t> liveIndexes;
	std::vector<Node> liveNodes;

	for (size_t i = 0; i < vec.size(); ++i)
	{
		std::string st_1 = vec[i].wordStamp;
		std::string st_2;

		for (size_t j = i + 1; j < vec.size(); ++j)
		{
			st_2 = vec[j].wordStamp;

			if (st_1.compare(st_2) == 0)
			{
				liveIndexes.push_back(i);
				liveIndexes.push_back(j);
			}
		}
	}

	for (size_t i = 0; i < vec.size(); ++i)
	{
		bool isAlive = false;
		for (size_t j = 0; j < liveIndexes.size(); ++j)
		{
			size_t li = liveIndexes[j];
			if (i == li)
			{
				isAlive = true;
			}
		}

		if (isAlive)
		{
			liveNodes.push_back(vec[i]);
		}
	}

	vec = liveNodes;
}

Node::Node(const Node &cpyObj)
{
	this->word = cpyObj.word;
	this->revWord = cpyObj.revWord;
	this->wordStamp = cpyObj.wordStamp;
	this->currentMapSquare = cpyObj.currentMapSquare;
	this->currentMapSquareIndex = cpyObj.currentMapSquareIndex;
	this->isMapSquareInit = cpyObj.isMapSquareInit;
	this->mapCharsDigits = cpyObj.mapCharsDigits;
}

Node::Node(const std::string &word)
{
	this->word = word;
	this->revWord = word;
	this->isMapSquareInit = false;

	std::reverse(this->revWord.begin(), this->revWord.end());

	this->buildStamp();
	this->resetMap();
}

void Node::buildStamp()
{
	std::vector<char> wordChars;
	for_each(this->word.begin(), this->word.end(),
		[&](char c)
	{
		wordChars.push_back(c);
	});

	std::sort(wordChars.begin(), wordChars.end());

	this->wordStamp = std::string(wordChars.begin(), wordChars.end());
}

void Node::resetMap()
{
	uint64_t t = pows[this->word.size() - 1];
	for (int i = 0; i < squares.size(); ++i)
	{
		if (squares[i] >= t)
		{
			this->currentMapSquareIndex = i;
			this->currentMapSquare = squaresRev[squares[i]];
			break;
		}
	}

	this->mapCharsDigits.clear();
	this->isMapSquareInit = false;
}

void load_precalculated_squares()
{
	uint64_t i = 1;
	uint64_t sq = i * i;
	uint64_t top = pows[10];

	while (sq < top)
	{
		if (is_square_has_unique_digits(sq))
		{
			squaresRev.insert(std::make_pair(sq, i));
			squares.insert(std::make_pair(i, sq));
		}

		++i;
		sq = i * i;
	}
}

bool is_square_has_unique_digits(uint64_t sq)
{
	std::map<int, int> digits;
	int counter = 0;
	while (sq > 0)
	{
		digits.insert(std::make_pair(sq % 10, 1));
		sq /= 10;
		++counter;
	}

	return digits.size() == counter;
}

void load_precalculated_pows()
{
	int i = 0;
	uint64_t pw = 1;
	while (i <= 10) // due to max length of available words. TODO: inject exponent as parameter..
	{
		pows.insert(std::make_pair(i, pw));
		++i;
		pw *= 10;
	}
}