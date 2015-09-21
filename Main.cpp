#include "Vigenere.h"
#include "BruteForce.h"

#include <stdio.h>
#include <string>
#include <iostream>

int main
	(
	int argc,
	char* argv[]
	)
{
	Vigenere myVigenere;
	BruteForce mBF;
	
	std::string cipher = "MSOKKJCOSXOEEKDTOSLGFWCMCHSUSGX";
	//myVigenere.test();

	mBF.loadDictionary(argv[1]);
	//printf("Initiating Decipher. . .\n");
	//mBF.crack(&cipher, 2, 6);
}