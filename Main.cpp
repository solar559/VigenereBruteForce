#include "Vigenere.h"
#include "BruteForce.h"

#include <stdio.h>
#include <string>
#include <iostream>
#include <ctime>
#include <cstdio>

int main
	(
	int argc,
	char* argv[]
	)
{
	if(argc != 2)
	{
		printf("Expecting a dictionary.txt file\nExiting. . .\n");
		return 0;
	}
	Vigenere myVigenere;
	BruteForce mBF;
	clock_t start;
	double duration;
	int userInput;

	while(userInput != 4)
	{
		printf("\n=============================================\n");
		printf("Choose one of the following options:\n");
		printf("1. Test Vigenere encrypt/decrypt\n");
		printf("2. Test rudimentary brute force algorithm\n");
		printf("3. Test optimized brute force algorithm\n");
		printf("4. exit\n");
		printf("=============================================\n");

		std::cin >> userInput;

		switch (userInput)
		{
			case 1:
				myVigenere.test();
				break;

			case 2:
				mBF.RunUnoptimizedTests(argv[1]);
				break;

			case 3:
				mBF.RunOptimizedTests(argv[1]);
				break;

			case 4:
				userInput = 4;
				break;

			default:
				printf("Unexpected input\n");
				break;
		}
	}
	return 0;
}
