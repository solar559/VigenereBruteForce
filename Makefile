main: main.o
	g++ -g -std=c++11 -o main main.o

main.o: Vigenere.h Vigenere.cpp BruteForce.h BruteForce.cpp main.cpp
	g++ -c -g -std=c++11  main.cpp

clean:
	rm *.o main
