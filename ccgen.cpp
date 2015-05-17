#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "styletype.hpp"

#define DEF 	0
#define	KNR 	1

using namespace std;

class readFile
{
	public:
		readFile(char* s) : i((s)) { currentTokenPos = currentLinePos = 0;}

		void getContents()
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
			i.close();
		}

		string getNextToken()
		{
			string gettableWord;
			gettableWord = tokenList[currentTokenPos];
			currentTokenPos++;
			return gettableWord;
		}

		string getNextLine()
		{
			string gettableLine;
			gettableLine = lineList[currentLinePos];
			currentLinePos++;
			return gettableLine;
		}

		bool hasMoreTokens()
		{
			if (currentTokenPos < static_cast<int>(tokenList.size())) return true;
			else return false;
		}
		
		bool hasMoreLines()
		{
			if (currentLinePos <  static_cast<int>(lineList.size())) return true;
			else return false;
		}

	private:
		ifstream i;
		vector<string> lineList;
		vector<string> tokenList;
		stringstream tokenbuf;
		//stringstream linebuf;
		string word,line;
		int currentTokenPos;
		int currentLinePos;
};


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
	readFile file(argv[1]);
	file.getContents();
	while (file.hasMoreTokens())
	{
		cout << file.getNextToken() << endl;
	}

	return 0;
}