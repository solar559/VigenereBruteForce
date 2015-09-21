#ifndef _BRUTE_FORCE_H_
#define _BRUTE_FORCE_H_

#include "Vigenere.h"

#include <string>
#include <set>
#include <vector>

class BruteForce
{
private:
	std::string*			cipherText;
	int						keyLength;
	int						firstWordLength;
	std::set<std::string>*	dictionary;
	std::set<std::string>::iterator dictIT;
	std::vector<std::string>* keys;

	void recursiveEnmuneration(std::vector<std::string>* keyStringVector, std::string prefix, int n, int prefixLength);

public:
	BruteForce();
	BruteForce(std::string* cText, int keyLen, int firstWordLen);
	~BruteForce();

	void crack(std::string* cText, int keyLen, int firstWordLen); 
	bool isAWord(std::string* word);
	void loadDictionary(char* dict);
	void enumerate(int a_keyLength);
};

#include "BruteForce.cpp"

#endif