#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "stylegen.hpp"

using namespace std;s

void usage()
{
	cout << "Usage: ./ccgen [inputfile] [outputfile]" << endl;
	exit(1);
}

int main(int argc, char* argv[])
{
	cout << "--------ccgen: A lightweight boilerplate C generator--------" << endl;
	cout << "---------------------Version 0.0.1--------------------------" << endl;
	if (argc < 3)
	{
		cout << "ERROR: No input Arguments Specified" << endl;
		usage();
	}
	return 0;
}