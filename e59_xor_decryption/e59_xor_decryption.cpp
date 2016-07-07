// Each character on a computer is assigned a unique code and the preferred standard is ASCII
// (American Standard Code for Information Interchange). For example, uppercase A = 65, asterisk(*) = 42, 
// and lowercase k = 107.
//
// A modern encryption method is to take a text file, convert the bytes to ASCII, then XOR each byte with a given value,
// taken from a secret key.The advantage with the XOR function is that using the same encryption key on the cipher text,
// restores the plain text; for example, 65 XOR 42 = 107, then 107 XOR 42 = 65.
//
// For unbreakable encryption, the key is the same length as the plain text message,
// and the key is made up of random bytes.The user would keep the encrypted message and the encryption key
// in different locations, and without both "halves", it is impossible to decrypt the message.
//
// Unfortunately, this method is impractical for most users, so the modified method is to use a password as a key.
// If the password is shorter than the message, which is likely, the key is repeated cyclically throughout
// the message.The balance for this method is using a sufficiently long password key for security, but short enough
// to be memorable.
//
// Your task has been made easy, as the encryption key consists of three lower case characters. 
// Using cipher.txt(right click and 'Save Link/Target As...'), a file containing the encrypted ASCII codes,
// and the knowledge that the plain text must contain common English words, decrypt the message and find the sum
// of the ASCII values in the original text.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#define MIN_READABLE_WORDS 50
#define CIPHERED_TEXT "p059_cipher.txt"
#define MOST_COMMON_WORDS "most_common_words.txt" // https://en.wikipedia.org/wiki/Most_common_words_in_English

void find_possible_cipher(const string, char, int, int *);
int count_valid_words(const string);
string decrypt(const string, const int *);
bool is_valid_ch(char, const string, int);
void print_stats(const string, const string);

const int CIPHER_LENGTH = 3;
int cipher[CIPHER_LENGTH] = { 0 };

int main()
{
	string msg;
	ifstream reader;
	reader.open(CIPHERED_TEXT);

	if (reader.is_open())
	{
		char ch; // buffer for the separator ","
		int t;
		while (reader >> t)
		{
			msg += (char)t;
			reader >> ch;
		}

		reader.close();
	}
	else
	{
		cout << "Unable to open file: " << CIPHERED_TEXT << endl;
		throw;
	}
	

	find_possible_cipher(msg, 'a', 0, cipher);

	return 0;
}

void find_possible_cipher(const string msg, char ch, int index, int *cipher)
{
	if (index == CIPHER_LENGTH)
	{
		string m = decrypt(msg, cipher);
		int c = count_valid_words(m);

		// if we have more than 50 valid words, we accept that the text is readable
		if (c > MIN_READABLE_WORDS)
		{
			string k;
			for (size_t i = 0; i < CIPHER_LENGTH; i++)
			{
				k += cipher[i];
			}

			print_stats(m, k);
		}

		return;
	}

	while (ch <= 'z')
	{
		// if the character is valid, we call recursively the function for other chars at the key
		if (is_valid_ch(ch, msg, index))
		{
			cipher[index] = ch;
			find_possible_cipher(msg, 'a', index + 1, cipher);
		}

		ch++;
	}
}

int count_valid_words(const string msg)
{
	// split message by empty space.. we accept that some words will contains punctuation signs
	vector<string> msg_words;
	stringstream sm(msg);
	string temp;
	while (sm.good())
	{
		getline(sm, temp, ' ');
		msg_words.push_back(temp);
	}

	// load dictionary
	// TODO: extract method
	ifstream reader;
	reader.open(MOST_COMMON_WORDS);
	if (reader.is_open())
	{
		getline(reader, temp);
		reader.close();
	}
	else
	{
		cout << "Unable to open file: " << MOST_COMMON_WORDS << endl;
		throw;
	}

	stringstream sd(temp);
	string buff;
	vector<string> dict_words;
	while (sd.good())
	{
		getline(sd, buff, ',');
		dict_words.push_back(buff);
	}

	// counting the valid words
	int c = 0;
	for (size_t i = 0; i < msg_words.size(); i++)
	{
		for (size_t j = 0; j < dict_words.size(); j++)
		{
			if (msg_words.at(i).compare(dict_words.at(j)) == 0)
			{
				c++;
			}
		}
	}

	return c;
}

string decrypt(const string msg, const int *cipher)
{
	string decrypted;
	for (size_t i = 0; i < msg.size(); i++)
	{
		decrypted += msg.at(i) ^ cipher[i % CIPHER_LENGTH];
	}

	return decrypted;
}

bool is_valid_ch(char ch, const string msg, int index)
{
	int xored;
	for (size_t i = index; i < msg.size(); i += CIPHER_LENGTH)
	{
		// char validation is based on ASCII codes.. all readable signs
		xored = msg.at(i) ^ ch;
		if (xored < 32 || xored > 122)
		{
			return false;
		}
	}

	return true;
}

void print_stats(const string msg, const string key)
{
	cout << "Possible cipher: " << key << endl;
	cout << "Decryption: " << msg << endl;

	int c = 0;
	for (size_t i = 0; i < msg.size(); i++)
	{
		c += msg.at(i);
	}

	cout << "Sum message ASCII codes: " << c << endl;
}
