#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdio>

#define SMART_CRACK (2)

static std::string alphebet[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z" };

/*---------------------------------------------------------*/
				// Private Methods //
/*---------------------------------------------------------*/
void BruteForce::recursiveEnumeration
(
	std::vector<std::string>* keyStringVector,
	std::string prefix,
	int keySetSize, // 26 for the letters of the alphebet
	int prefixLength // length of the key
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
		if(newPrefix.length() > 2)
		{
			if(newPrefix.at(newPrefix.length()-3) == newPrefix.at(newPrefix.length()-2) && newPrefix.at(newPrefix.length()-2) == newPrefix.at(newPrefix.length()-1))
			{
				// First three letter match so ditch this string.
			}
			else
			{
				recursiveEnumeration(keyStringVector, newPrefix, keySetSize, prefixLength - 1);
			}
		}
		else
		{
			recursiveEnumeration(keyStringVector, newPrefix, keySetSize, prefixLength - 1);
		}
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
		recursiveEnumeration(keys, prefix, 26, keyLen);
	} 
	else
	{
		keys->clear();
		recursiveEnumeration(keys, prefix, 26, keyLen);
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

// We need to enumerate the keys for the first time before doing this.
bool BruteForce::intelligentCrack(std::string* cText, int keyLen, int firstWordLen, int curKeyEnumLength, std::string curKeyEnum)
{
	Vigenere bruteVigenere;
	std::string substr;
	std::string decryptedWord;
	std::vector<std::string> curKeysEnum_vector;

	if(curKeyEnumLength == 0)
	{
		recursiveEnumeration(&curKeysEnum_vector, curKeyEnum, 26, 2);
		curKeyEnumLength = 2;
	}
	else
	{
		recursiveEnumeration(&curKeysEnum_vector, curKeyEnum, 26, 1);
	}

	for(auto it = curKeysEnum_vector.begin(); it != curKeysEnum_vector.end(); it++)
	{
		std::string keyKey = *it;

		// The key has reached its full length
		if(curKeyEnumLength == keyLen)
		{
			substr = (cText->substr(0, firstWordLen));
			decryptedWord = bruteVigenere.decrypt(&substr, &keyKey);
			if(isAWord(&decryptedWord))
			{
				std::cout << "\t---------Solution found---------\n";
				//std::cout << "Timer: " << duration << std::endl;
				std::cout << "key: " << keyKey << std::endl;
				std::cout << bruteVigenere.decrypt(cText, &keyKey) << std::endl;
				return true;
			}
		}
		else // Key is still not full length
		{
			substr = (cText->substr(0, curKeyEnumLength));
			decryptedWord = bruteVigenere.decrypt(&substr, &keyKey);

			if (intelligentIsAWord(&decryptedWord, curKeyEnumLength))
			{
				if(curKeyEnumLength == firstWordLen)
				{
					std::cout << "\t---------Solution found---------\n";
					std::cout << "key: " << curKeyEnum << std::endl;
					std::cout << bruteVigenere.decrypt(cText, &curKeyEnum) << std::endl;
					return true;
				}
				if(curKeyEnumLength < keyLen)
				{
					// Add another letter onto the key and try again
					if(intelligentCrack(cText, keyLen, firstWordLen, (curKeyEnumLength+1), *it))
					{
						// Used to break out of all the for loops on the stack
						return true;
					}
				}
			}
		}
	}
	return false;
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

bool BruteForce::intelligentIsAWord(std::string* word, int length)
{
	std::string dictWord;

	for(auto it = dictionary->begin(); it != dictionary->end(); it++)
	{
		dictWord = it->substr(0, length);
		if(dictWord.compare(*word) == 0)
		{
			return true;
		}
	}
	return false;
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
	std::string prefix = "abc";
	keys = new std::vector<std::string>;
	std::clock_t start;
	double duration;

	start = std::clock();
	recursiveEnumeration(keys, prefix, 26, a_keyLength);
	duration = (std::clock() - start)/(double)CLOCKS_PER_SEC;

	std::cout<<"Time to Generate keys: " << duration << " seconds\n";
}

void BruteForce::RunUnoptimizedTests(char* dictionary_file)
{
	clock_t start;
	double duration;
	std::string cipher1 = "MSOKKJCOSXOEEKDTOSLGFWCMCHSUSGX";
	std::string cipher2 = "OOPCULNWFRCFQAQJGPNARMEYUODYOUNRGWORQEPVARCEPBBSCEQYEARAJUYGWWYACYWBPRNEJBMDTEAEYCCFJNENSGWAQRTSJTGXNRQRMDGFEEPHSJRGFCFMACCB";
	std::string cipher3 = "MTZHZEOQKASVBDOWMWMKMNYIIHVWPEXJA";
	std::string cipher4 = "HUETNMIXVTMQWZTQMMZUNZXNSSBLNSJVSJQDLKR";
	std::string cipher5 = "LDWMEKPOPSWNOAVBIDHIPCEWAETYRVOAUPSINOVDIEDHCDSELHCCPVHRPOHZUSERSFS";
	std::string cipher6 = "VVVLZWWPBWHZDKBTXLDCGOTGTGRWAQWZSDHEMXLBELUMO";

	// Using the unrefined decrypter
	printf("Initiating Decipher. . .\n");
	loadDictionary(dictionary_file, 7);
	crack(&cipher1, 2, 6);

	loadDictionary(dictionary_file, 8);
	crack(&cipher2, 3, 7);

	loadDictionary(dictionary_file, 11);
	crack(&cipher3, 4, 10);

	loadDictionary(dictionary_file, 12);
	crack(&cipher4, 5, 11);

	loadDictionary(dictionary_file, 7);
	crack(&cipher5, 6, 9);

	loadDictionary(dictionary_file, 8);
	crack(&cipher6, 7, 13);
}

void BruteForce::RunOptimizedTests(char* dictionary_file)
{
	clock_t start;
	double duration;
	std::string cipher1 = "MSOKKJCOSXOEEKDTOSLGFWCMCHSUSGX";
	std::string cipher2 = "OOPCULNWFRCFQAQJGPNARMEYUODYOUNRGWORQEPVARCEPBBSCEQYEARAJUYGWWYACYWBPRNEJBMDTEAEYCCFJNENSGWAQRTSJTGXNRQRMDGFEEPHSJRGFCFMACCB";
	std::string cipher3 = "MTZHZEOQKASVBDOWMWMKMNYIIHVWPEXJA";
	std::string cipher4 = "HUETNMIXVTMQWZTQMMZUNZXNSSBLNSJVSJQDLKR";
	std::string cipher5 = "LDWMEKPOPSWNOAVBIDHIPCEWAETYRVOAUPSINOVDIEDHCDSELHCCPVHRPOHZUSERSFS";
	std::string cipher6 = "VVVLZWWPBWHZDKBTXLDCGOTGTGRWAQWZSDHEMXLBELUMO";

	// Testing the intelligent algorithm
	loadDictionary(dictionary_file, 7);
	start = clock();
	intelligentCrack(&cipher1, 2, 6, 0, "");
	duration = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout << "Intelligent time: " << duration <<std::endl;
	std::cout << "\t--------------------------------\n";
	std::cout << "     ===== End Timed Deciphering =====   \n";
	std::cout << "==========================================\n\n";

	loadDictionary(dictionary_file, 8);
	start = clock();
	intelligentCrack(&cipher2, 3, 7, 0, "");
	duration = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout << "Intelligent time: " << duration <<std::endl;
	std::cout << "\t--------------------------------\n";
	std::cout << "     ===== End Timed Deciphering =====   \n";
	std::cout << "==========================================\n\n";

	loadDictionary(dictionary_file, 11);
	start = clock();
	intelligentCrack(&cipher3, 4, 10, 0, "");
	duration = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout << "Intelligent time: " << duration <<std::endl;
	std::cout << "\t--------------------------------\n";
	std::cout << "     ===== End Timed Deciphering =====   \n";
	std::cout << "==========================================\n\n";

	loadDictionary(dictionary_file, 12);
	start = clock();
	intelligentCrack(&cipher4, 5, 11, 0, "");
	duration = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout << "Intelligent time: " << duration <<std::endl;
	std::cout << "\t--------------------------------\n";
	std::cout << "     ===== End Timed Deciphering =====   \n";
	std::cout << "==========================================\n\n";

	loadDictionary(dictionary_file, 7);
	start = clock();
	intelligentCrack(&cipher5, 6, 9, 0, "");
	duration = (clock() - start)/(double)CLOCKS_PER_SEC;
	std::cout << "Intelligent time: " << duration <<std::endl;
	std::cout << "\t--------------------------------\n";
	std::cout << "     ===== End Timed Deciphering =====   \n";
	std::cout << "==========================================\n\n";
}

