#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void usage()
{
	cout << "Usage: ./ccgen [inputfile] [outputfile]" << endl;
	exit(1);
}


int main(int argc, char* argv[])
{

	if (argc == 1)
	{
		cout << "Error: No input Arguments Specified" << endl;
		usage();
	}
	return 0;
}