
#include <iostream>

#define LOWER_CASE_A ( 97 )
#define UPPER_CASE_A ( 65 )
#define LOWER_CASE_Z ( 122 )
#define UPPER_CASE_Z ( 91 )

Vigenere::Vigenere()
{
}

/*
* Using a Vigenere Cipher Algorithm, this function
* will encrypt the given text with the given key
*
* NOTE: The text should first be converted to All Caps
*       and all special characters/spaces should be removed
*/
std::string Vigenere::encrypt
(
std::string* const plaintext,
std::string* const key
)
{
	int			keyIndex = 0;
	int			encryptedValue = 0;
	std::string	encryptedText = "";
	char		curPTLetter;
	char		curKeyLetter;
	char		charEncrypLetter;
	std::string encryptedLetter;

	for (int i = 0; i < plaintext->length(); i++)
	{
		if (keyIndex >= key->length())
		{
			keyIndex = 0;
		}
		curPTLetter = plaintext->at(i);
		curKeyLetter = key->at(keyIndex++);

		// Encrypt the letter
		encryptedValue = ((curPTLetter + curKeyLetter) % 26);
		if (encryptedValue < 0)
		{
			charEncrypLetter = (char)(encryptedValue + UPPER_CASE_Z);
		}
		else
		{
			charEncrypLetter = (char)(encryptedValue + UPPER_CASE_A);
		}

		encryptedLetter = charEncrypLetter;
		encryptedText.append(encryptedLetter);
	}

	return encryptedText;
}

std::string Vigenere::decrypt
(
std::string* const cipherText,
std::string* const key
)
{
	int			keyIndex = 0;
	int			encryptedValue;
	std::string	decryptedText = "";
	char		curCipherLetter;
	char		curKeyLetter;
	char		charDecryptedLetter;
	std::string decryptedLetter;

	for (int i = 0; i < cipherText->length(); i++)
	{
		if (keyIndex >= key->length())
		{
			keyIndex = 0;
		}
		curCipherLetter = cipherText->at(i);
		curKeyLetter = key->at(keyIndex++);

		// Encrypt the letter
		encryptedValue = ((curCipherLetter - curKeyLetter) % 26);
		if (encryptedValue < 0)
		{
			charDecryptedLetter = (char)(encryptedValue + UPPER_CASE_Z);
		}
		else
		{
			charDecryptedLetter = (char)(encryptedValue + UPPER_CASE_A);
		}

		decryptedLetter = charDecryptedLetter;
		decryptedText.append(decryptedLetter);
	}
//std::cout << "Key: " << *key << "\tPlaintext: " << decryptedText << std::endl;
	return decryptedText;
}

/*
* Removes all characters except letter and 
* Sets all characters to upper case
*/
void Vigenere::toUpperCase(std::string* plaintext)
{
	char curChar;
	std::string dummyString;

	for (int i = 0; i < plaintext->length(); i++)
	{
		curChar = plaintext->at(i);

		// If a character is within the range of the lower case alphabet
		// then it will be replaced with its uppercase equivelant.
		// NOTE: this only modifies lower case letters. Special characters
		//       are left alone.
		if ((curChar >= LOWER_CASE_A) && (curChar <= LOWER_CASE_Z))
		{
			curChar = curChar - 32;
			dummyString = curChar;
			plaintext->replace(i, 1, dummyString);
		}
		else if (!((curChar >= UPPER_CASE_A) && (curChar <= UPPER_CASE_Z)))
		{
			plaintext->erase(i, 1);
			// Step i backwards because the string was shortened
			i--;
		}
	}
}

void Vigenere::test()
{
	int userInput;
	std::string plainText;
	std::string key;
	std::string encryptedText;

	userInput = 0;

	while(userInput != 2)
	{
		printf("\n--------------------------------------\n");
		printf("User Options:\n");
		printf("1: Enter new plain text/key combo.\n");
		printf("2: exit\n");

		std::cin >> userInput;

		switch (userInput)
		{
		case(1) :
			printf("Type plaintext. Press enter when finished\n");
			std::cin >> plainText;
			printf("Type a keyword followed by <enter>\n");
			std::cin >> key;

			toUpperCase(&plainText);
			toUpperCase(&key);
			encryptedText = encrypt(&plainText, &key);
			plainText = decrypt(&encryptedText, &key);

			std::cout << "Encrypted Text:\n" << encryptedText << std::endl;
			std::cout << "Decrypted Text:\n" << plainText << std::endl;
			break;

		case(2) :
			printf("Exiting.\n");
			userInput = 2;
		}
	}
}
