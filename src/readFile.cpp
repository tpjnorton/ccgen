// Copyright Tom Norton 2017.
#include "readFile.hpp"

readFile::readFile(char *s) : i((s)) {
  currentTokenPos = currentLinePos = 0;
}

void readFile::getContents() {
  while (i.peek() != EOF) {
    getline(i, line);
    stringstream linebuf(line);
    stringMetadata lineStruct;
    lineStruct.line = line;
    lineStruct.lineNo = currentLine;
    lineList.push_back(lineStruct);

    while (linebuf.good()) {
      stringMetadata wordStruct;
      getline(linebuf, word, ' ');

      if (word != "") {
        wordStruct.line = word;
        wordStruct.lineNo = currentLine;
        // cout << currentLine << endl;
        tokenList.push_back(wordStruct);
      }
        // cout << word << endl;
    }

    currentLine++;
  }
  i.close();
}

string readFile::getNextToken() {
  string gettableWord;
  gettableWord = tokenList[currentTokenPos].line;
  currentTokenPos++;
  return gettableWord;
}

string readFile::getNextLine() {
  string gettableLine;
  gettableLine = lineList[currentLinePos].line;
  currentLinePos++;
  return gettableLine;
}

string readFile::getPrevLine() {
  currentLinePos--;
  string gettableLine;
  gettableLine = lineList[currentLinePos].line;
  return gettableLine;
}

string readFile::getPrevToken() {
  currentTokenPos--;
  string gettableWord;
  gettableWord = tokenList[currentTokenPos].line;
  return gettableWord;
}

string readFile::peekNextLine() {
  string gettableLine;
  gettableLine = lineList[currentLinePos].line;
  return gettableLine;
}

string readFile::peekNextToken() {
  string gettableWord;
  gettableWord = tokenList[currentTokenPos].line;
  return gettableWord;
}

int readFile::getLineNo() {
  int lineNo;
  lineNo = tokenList[currentTokenPos].lineNo;
  return lineNo;
}

bool readFile::hasMoreTokens() {
  if (currentTokenPos < static_cast<int>(tokenList.size()))
    return true;
  else
    return false;
}

bool readFile::hasMoreLines() {
  if (currentLinePos <  static_cast<int>(lineList.size()))
    return true;
  else
    return false;
}
