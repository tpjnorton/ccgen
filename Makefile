clean:
	rm -f cgen *.c

all:
	g++ -O3 -Wall cgen.cpp -o cgen

remake:
	rm -f cgen *.c
	g++ -O3 -Wall cgen.cpp -o cgen