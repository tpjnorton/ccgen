clean:
	rm -f build/ccgen *.c

all:
	g++ -O3 -Wall src/*.cpp -o build/ccgen

default:
	all
remake:
	rm -f build/ccgen *.c
	g++ -O3 -Wall src/*.cpp -o build/ccgen