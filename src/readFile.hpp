// Copyright Tom Norton 2017.

#ifndef SRC_READFILE_HPP_
  #define SRC_READFILE_HPP_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

struct stringMetadata {
  string line;
  int lineNo;
};

class readFile {
  public:
    readFile(char* s);
    void getContents();
    string getNextToken();
    string getNextLine();
    string getPrevLine();
    string getPrevToken();
    string peekNextLine();
    string peekNextToken();
    int getLineNo();
    bool hasMoreTokens();
    bool hasMoreLines();

  private:
    ifstream i;
    vector<stringMetadata> lineList;
    vector<stringMetadata> tokenList;
    string word, line;
    int currentTokenPos;
    int currentLinePos;
    int currentLine;
};

#endif  // SRC_READFILE_HPP_
