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
	std::set<std::string>* 	repeatedFirstLetterDict;
	std::vector<std::string>* keys;

	void recursiveEnumeration(std::vector<std::string>* keyStringVector, std::string prefix, int n, int prefixLength);

public:
	BruteForce();
	BruteForce(std::string* cText, int keyLen, int firstWordLen);
	~BruteForce();

	void crack(std::string* cText, int keyLen, int firstWordLen); 
	bool intelligentCrack(std::string* cText, int keyLen, int firstWordLen, int curKeyEnumLength, std::string curKeyEnum);
	bool isAWord(std::string* word);
	bool intelligentIsAWord(std::string* word, int length);
	void loadDictionary(char* dict, int keyLen);
	void enumerate(int a_keyLength);

	void RunUnoptimizedTests(char* dictionary_file);
	void RunOptimizedTests(char* dictionary_file);
};

#include "BruteForce.cpp"

#endif