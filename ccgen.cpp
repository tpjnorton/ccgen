#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "stylegen.hpp"

using namespace std;

class readFile
{
	public:
		ifstream i;
		vector<string> lineList;
		vector<string> tokenList;
		stringstream tokenbuf;
		//stringstream linebuf;
		string word,line;

		readFile(char* s) : i((s)) {}

		void get_contents()
		{
			while (i.peek() != EOF)
			{
				getline(i,line);
				stringstream linebuf(line);
				lineList.push_back(line);

				while (linebuf.good())
				{
					getline(linebuf,word,' ');
					tokenList.push_back(word);
			    	// cout << word << endl;
				}
			}
		}

};


void usage()
{
	cout << "Usage: ./ccgen [inputfile] [outputfile]" << endl;
	exit(1);
}

int main(int argc, char* argv[])
{
	readFile file(argv[1]);
	file.get_contents();
	cout << "--------ccgen: A lightweight boilerplate C generator--------" << endl;
	cout << "---------------------Version 0.0.1--------------------------" << endl;
	if (argc < 3)
	{
		cout << "ERROR: No input Arguments Specified" << endl;
		usage();
	}
	// unsigned i = 0;
	// while (i<file.tokenList.size())
	// {
	// 	cout << file.tokenList[i] << endl;
	// 	i++;
	// }

	return 0;
}