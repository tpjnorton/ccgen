clean:
	rm -f build/ccgen *.c

all:
	g++ -O3 -Wall ccgen.cpp -o build/ccgen

remake:
	rm -f ccgen *.c
	g++ -O3 -Wall ccgen.cpp -o build/ccgen