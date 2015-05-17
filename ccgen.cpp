#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "styletype.hpp"
#include <unistd.h>

#define DEF 	0
#define	KNR 	1

using namespace std;

int codingStyle = 0;
stringstream outputbuffer;

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

bool parseTokens(readFile &file)
{
	bool understood = false;
	outputbuffer << def_include;
	while (file.hasMoreTokens())
	{
		string currToken = file.getNextToken();
		understood = false;

		if (currToken == "STYLE")
		{
			currToken = file.getNextToken();
			
			if (currToken == "DEF")
			{
				codingStyle = DEF;
				understood = true;
			}

			else if (currToken == "KNR")
			{
				codingStyle = KNR;
				understood = true;
			}
		}

		else if (currToken == "IF")
		{
			currToken = file.getNextToken();
			
			if (currToken == "MULT")
			{
				if (codingStyle == KNR)
				{
					outputbuffer << if_knr;
					understood = true;
				}

				else if (codingStyle == DEF)
				{
					outputbuffer << if_default;
					understood = true;
				}

				understood = true;
			}

			else if (currToken == "ONE")
			{
				outputbuffer << if_one_line;
				understood = true;
			}
		}

		else if (currToken == "ELIF")
		{
			currToken = file.getNextToken();
			
			if (currToken == "MULT")
			{
				if (codingStyle == KNR)
				{
					outputbuffer << else_if_knr;
					understood = true;
				}

				else if (codingStyle == DEF)
				{
					outputbuffer << else_if_default;
					understood = true;
				}

				understood = true;
			}

			else if (currToken == "ONE")
			{
				outputbuffer << else_if_one_line;
				understood = true;
			}
		}

		else if (currToken == "ELSE")
		{
			currToken = file.getNextToken();
			
			if (currToken == "MULT")
			{
				if (codingStyle == KNR)
				{
					outputbuffer << else_knr;
					understood = true;
				}

				else if (codingStyle == DEF)
				{
					outputbuffer << else_default;
					understood = true;
				}

				understood = true;
			}

			else if (currToken == "ONE")
			{
				outputbuffer << else_one_line;
				understood = true;
			}
		}

		else if (currToken == "MAIN")
		{
			currToken = file.getNextToken();
			
			if (currToken == "ARG")
			{
				if (codingStyle == KNR)
				{
					outputbuffer << arg_main_knr;
					understood = true;
				}

				else if (codingStyle == DEF)
				{
					outputbuffer << arg_main_default;
					understood = true;
				}

				understood = true;
			}

			else if (currToken == "VOID")
			{
				if (codingStyle == KNR)
				{
					outputbuffer << void_main_knr;
					understood = true;
				}

				else if (codingStyle == DEF)
				{
					outputbuffer << void_main_default;
					understood = true;
				}

				understood = true;
			}
		}


		if (!understood) return false;
	}

	if (understood) return true;
	return false;
}

int main(int argc, char* argv[])
{
	cout << "--------ccgen: A lightweight boilerplate C generator--------" << endl;
	cout << "---------------------Version 0.0.1.1------------------------" << endl;
	if (argc < 3)
	{
		cout << "ERROR: No input Arguments Specified" << endl;
		usage();
	}
	readFile file(argv[1]);
	cout << "Reading file..." << endl;
	file.getContents();
	usleep(500000);
	cout << "File Read Succesful." << endl;
	usleep(500000);
	cout << "Parsing file..." << endl;
	usleep(500000);
	bool retval = parseTokens(file);
	cout << "DONE" << endl;
	cout << "parse = "<< boolalpha << retval << endl;
	string currentStructure;
	ofstream o(argv[2]);



	currentStructure = outputbuffer.str();
	o << currentStructure;


	return retval;
}