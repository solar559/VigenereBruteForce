#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdio>

static std::string alphebet[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

/*---------------------------------------------------------*/
				// Private Methods //
/*---------------------------------------------------------*/
void BruteForce::recursiveEnmuneration
(
	std::vector<std::string>* keyStringVector,
	std::string prefix,
	int keySetSize,
	int prefixLength
)
{
	if (prefixLength == 0)
	{
		int sequenceStartIndex = 0;
		bool inSequence = false;
		for(int i = 0; i < prefix.length()-1; i++)
		{
			if(prefix.at(i) == prefix.at(i+1))
			{
				if(!inSequence)
				{
					inSequence = true;
					sequenceStartIndex = i;
				}
				else // Already in a sequence
				{
					// We already found 2 matching 1's
					if((i - sequenceStartIndex) == 1)
					{
						// Do not push the string onto
						// the vector because it has
						// 3 letters in a row the same
						return;
					}
				}
			}
			else
			{
				inSequence = false;
			}
		}
		keyStringVector->push_back(prefix);
		return;
	}

	for (int i = 0; i < keySetSize; i++)
	{
		std::string newPrefix = prefix + alphebet[i];
		recursiveEnmuneration(keyStringVector, newPrefix, keySetSize, prefixLength - 1);
	}
}

BruteForce::BruteForce() : 
	  cipherText(nullptr) 
	, keyLength(0) 
	, firstWordLength(0)
	, keys(nullptr)
{
	dictionary = new std::set<std::string>;
	repeatedFirstLetterDict = new std::set<std::string>;
	dictIT = dictionary->begin();
}

BruteForce::BruteForce(std::string* cText, int keyLen, int firstWordLen)
{
	cipherText = cText;
	keyLength = keyLen;
	firstWordLen = firstWordLength;
	dictionary = new std::set<std::string>;
	repeatedFirstLetterDict = new std::set<std::string>;
	dictIT = dictionary->begin();
	keys = nullptr;
}

BruteForce::~BruteForce()
{
	if (dictionary != nullptr)
	{
		dictionary->clear();
		delete dictionary;
		dictionary = nullptr;
	}
	if (repeatedFirstLetterDict != nullptr)
	{
		repeatedFirstLetterDict->clear();
		delete repeatedFirstLetterDict;
		repeatedFirstLetterDict = nullptr;
	}
	if (keys != nullptr)
	{
		keys->clear();
		delete keys;
		keys = nullptr;
	}
}

void BruteForce::crack(std::string* cText, int keyLen, int firstWordLen)
{
	Vigenere bruteVigenere;
	std::string stringKey;
	std::string firstWord;
	std::string decryptedWord;
	std::clock_t start;
	double duration;

	firstWord = cText->substr(0, firstWordLen);

	//Generate all possible keys
	std::string prefix = "";
	if(keys == nullptr)
	{
		keys = new std::vector<std::string>;
		recursiveEnmuneration(keys, prefix, 26, keyLen);
	} 
	else
	{
		keys->clear();
		recursiveEnmuneration(keys, prefix, 26, keyLen);
	}

	std::cout << "==========================================\n";
	std::cout << "    ===== Begin Timed Deciphering =====   \n";
	std::cout << "First Word: " << firstWord << std::endl;
	std::cout << "Deciphering: " << *cText << std::endl;

	// Start Timer
	start = std::clock();

	for(auto it = keys->begin(); it != keys->end(); it++)
	{
		stringKey = *it;

		decryptedWord = bruteVigenere.decrypt(&firstWord, &stringKey);

		if (isAWord(&decryptedWord))
		{
			// End timer
			duration = (std::clock() - start)/(double)CLOCKS_PER_SEC;
			std::cout << "\t---------Solution found---------\n";
			std::cout << "Timer: " << duration << std::endl;
			std::cout << "key: " << stringKey << std::endl;
			std::cout << bruteVigenere.decrypt(cText, &stringKey) << std::endl;
			std::cout << "\t--------------------------------\n";
			std::cout << "     ===== End Timed Deciphering =====   \n";
			std::cout << "==========================================\n\n";
			return;
		}
	}
	duration = (std::clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout << "Timer: " << duration << std::endl;
	std::cout << "     DECIPHERING FAILED \n";
	std::cout << "==========================================\n\n";
}

bool BruteForce::isAWord(std::string* word)
{
	bool status = false;

	std::set<std::string>::iterator it;
	it = dictionary->find(*word);

	if(it == dictionary->end())
	{
		status = false;
	}
	else
	{
		status = true;
	}

	return status;
}

/*
* @param keyLen must be one more than the key length letter count
*/
void BruteForce::loadDictionary(char* dict, int keyLen)
{
	// Ensure that the dictionaries are empty.
	dictionary->clear();
	repeatedFirstLetterDict->clear();

	std::ifstream dictionaryFile;
	std::string word;

	// Setting up the set iterator
	dictIT = dictionary->begin();

	// Opening file and reading
	dictionaryFile.open(dict);
	if (dictionaryFile.good())
	{
		while (!dictionaryFile.eof())
		{
			getline(dictionaryFile, word);

			// Only insert the words if they are the right length
			if(word.length() == keyLen)
			{
				if(word.at(0) == word.at(1))
				{
					repeatedFirstLetterDict->insert(word);
				}
				//Removes the carriage return and stores the word
				dictionary->insert(dictIT, word.erase(word.length() -1));
			}
		}
	}
}

void BruteForce::enumerate(int a_keyLength)
{
	std::string prefix = "";
	keys = new std::vector<std::string>;
	recursiveEnmuneration(keys, prefix, 26, a_keyLength);

	
	for (auto it = keys->begin(); it != keys->end(); it++)
	{
		std::cout << *it << std::endl;
	}
	printf("\nSize of vect: %d\n", keys->size()); //17576
	
}



