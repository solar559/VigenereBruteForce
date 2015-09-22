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
	
	std::string cipher1 = "MSOKKJCOSXOEEKDTOSLGFWCMCHSUSGX";
	std::string cipher2 = "OOPCULNWFRCFQAQJGPNARMEYUODYOUNRGWORQEPVARCEPBBSCEQYEARAJUYGWWYACYWBPRNEJBMDTEAEYCCFJNENSGWAQRTSJTGXNRQRMDGFEEPHSJRGFCFMACCB";
	std::string cipher3 = "MTZHZEOQKASVBDOWMWMKMNYIIHVWPEXJA";
	std::string cipher4 = "HUETNMIXVTMQWZTQMMZUNZXNSSBLNSJVSJQDLKR";
	std::string cipher5 = "LDWMEKPOPSWNOAVBIDHIPCEWAETYRVOAUPSINOVDIEDHCDSELHCCPVHRPOHZUSERSFS";
	std::string cipher6 = "VVVLZWWPBWHZDKBTXLDCGOTGTGRWAQWZSDHEMXLBELUMO";
/*
	// Decipher
	printf("Initiating Decipher. . .\n");
	mBF.loadDictionary(argv[1], 7);
	mBF.crack(&cipher1, 2, 6);

	mBF.loadDictionary(argv[1], 8);
	mBF.crack(&cipher2, 3, 7);

	mBF.loadDictionary(argv[1], 11);
	mBF.crack(&cipher3, 4, 10);

	mBF.loadDictionary(argv[1], 12);
	mBF.crack(&cipher4, 5, 11);
*/
	mBF.loadDictionary(argv[1], 7);
	mBF.crack(&cipher5, 6, 9);
/*
	mBF.loadDictionary(argv[1], 8);
	mBF.crack(&cipher6, 7, 13);
*/
	return 0;
}
