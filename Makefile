my_morse: morse.o
	g++ morse.o -std=c++11 -o my_morse

morse.o: morse.cpp
	g++ -c morse.cpp

clean:
	rm *.o my_morse
