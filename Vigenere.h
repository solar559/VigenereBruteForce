#ifndef _VIGENERE_H_
#define _VIGENERE_H_

#include <string>

class Vigenere
{
public:
	Vigenere();

	std::string encrypt
		(
		std::string* const plaintext,
		std::string* const key
		);

	std::string decrypt
		(
		std::string* const cipherText,
		std::string* const key
		);

	void toUpperCase(std::string* plaintext);

	void test();
};

#include "Vigenere.cpp"

#endif
