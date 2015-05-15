clean:
	rm -f ccgen *.c

all:
	g++ -O3 -Wall ccgen.cpp -o ccgen

remake:
	rm -f ccgen *.c
	g++ -O3 -Wall ccgen.cpp -o ccgen