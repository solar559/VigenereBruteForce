main: main.o
	g++ -g -o main main.o

main.o: Vigenere.h Vigenere.cpp BruteForce.h BruteForce.cpp
	g++ -c -g main.cpp

clean:
	rm *.o main
