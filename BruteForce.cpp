#include <fstream>
#include <iostream>

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
	dictionary = new std::set < std::string > ;
	dictIT = dictionary->begin();
}

BruteForce::BruteForce(std::string* cText, int keyLen, int firstWordLen)
{
	cipherText = cText;
	keyLength = keyLen;
	firstWordLen = firstWordLength;
	dictionary = new std::set < std::string > ;
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
	if (keys != nullptr)
	{
		keys->clear();
		delete keys;
		keys = nullptr;
	}
}

void BruteForce::crack(std::string* cText, int keyLen, int firstWordLen)
{
	// Set private variables
	cipherText = cText;
	keyLength = keyLen;
	firstWordLength = firstWordLen;

	Vigenere bruteVigenere;
	std::string stringKey;
	std::string firstWord;
	std::string decryptedWord;

	firstWord = cText->substr(0, firstWordLength);

	//Generate all possible keys
	std::string prefix = "";
	if(keys == nullptr)
	{
		keys = new std::vector < std::string > ;
		recursiveEnmuneration(keys, prefix, 26, keyLen);
	} 
	else
	{
		printf("Keys have already been enumerated\n Exiting\n");
		return;
	}

std::cout << "Dictionary size: " << dictionary->size() << std::endl;
std::cout << "First Word: " << firstWord << std::endl;
std::cout << "Deciphering: " << *cText << std::endl;

int counter = 0;
	for(auto it = keys->begin(); it != keys->end(); it++)
	{
		counter++;
		stringKey = *it;

		decryptedWord = bruteVigenere.decrypt(&firstWord, &stringKey);

		if (isAWord(&decryptedWord))
		{
			std::cout << "---------Solution found---------\n";
			std::cout << "key: " << decryptedWord << std::endl;
			return;
		}
	}
	std::cout << "\ncounter : "<<counter<<std::endl;
}

bool BruteForce::isAWord(std::string* word)
{
	bool status = false;

	std::set<std::string>::iterator it;
	it = dictionary->find(*word);

	if(word->compare("CAESAR"))
	{
		std::cout << *word << std::endl;
		std::cout << *dictionary->find("CAESAR") << std::endl;
	}

	if(it == dictionary->end())
	{
		status = false;
//std::cout << *word << ": " << status << std::endl;
	}
	else
	{
		status = true;
	}

	return status;
}

void BruteForce::loadDictionary(char* dict)
{
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
			dictionary->insert(dictIT, word);
		}
		
		std::cout << std::endl << "Dictionary Size: " << dictionary->size() << std::endl;
		
		auto it = dictionary->find("WRONGHEADEDNESS");
		if(it == dictionary->end())
		{
			std::cout << "WRONGHEADEDNESS is not in the dict?\n";
		}
		else
		{
			std::cout << "Found WRONGHEADEDNESS: " << *it << std::endl;
		}
	}
}

void BruteForce::enumerate(int a_keyLength)
{
	std::string prefix = "";
	keys = new std::vector < std::string >;
	recursiveEnmuneration(keys, prefix, 26, a_keyLength);

	/*
	for (auto it = keys->begin(); it != keys->end(); it++)
	{
		std::cout << *it << " ";
	}
	printf("\nSize of vect: %d\n", keys->size()); //17576
	*/
}



