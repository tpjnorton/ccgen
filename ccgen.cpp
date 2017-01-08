#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "styletype.hpp"
#include <unistd.h>

#define DEF   0
#define KNR   1

using namespace std;

int codingStyle = 0;
bool mainDeclared = false;
bool inFunction = false;
int numFunctions = 0;
int currentLine = 0;

struct stringMetadata
{
  string line;
  int lineNo;
};

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
        stringMetadata lineStruct;
        lineStruct.line = line;
        lineStruct.lineNo = currentLine;
        lineList.push_back(lineStruct);

        while (linebuf.good())
        {
          stringMetadata wordStruct;
          getline(linebuf,word,' ');

          if (word != "")
          {     
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

    string getNextToken()
    {
      string gettableWord;
      gettableWord = tokenList[currentTokenPos].line;
      currentTokenPos++;
      return gettableWord;
    }

    string getNextLine()
    {
      string gettableLine;
      gettableLine = lineList[currentLinePos].line;
      currentLinePos++;
      return gettableLine;
    }

    string getPrevLine()
    {
      currentLinePos--;
      string gettableLine;
      gettableLine = lineList[currentLinePos].line;
      return gettableLine;
    }

    string getPrevToken()
    {
      currentTokenPos--;
      string gettableWord;
      gettableWord = tokenList[currentTokenPos].line;
      return gettableWord;
    }

    string peekNextLine()
    {
      string gettableLine;
      gettableLine = lineList[currentLinePos].line;
      return gettableLine;
    }

    string peekNextToken()
    {
      string gettableWord;
      gettableWord = tokenList[currentTokenPos].line;
      return gettableWord;
    }

    int getLineNo()
    {
      int lineNo;
      lineNo = tokenList[currentTokenPos].lineNo;
      return lineNo;
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
    vector<stringMetadata> lineList;
    vector<stringMetadata> tokenList;
    string word,line;
    int currentTokenPos;
    int currentLinePos;
};

void addTabs(stringstream &outputBuffer, int tabCount)
{
  int i = 0;

  for(i = 0; i<tabCount; i++)
  {
    outputBuffer << std_tab;
  }
}

void usage()
{
  cout << "Usage: ./ccgen [inputfile] [outputfile]" << endl;
  exit(1);
}

bool parseTokens(readFile &file, stringstream &outputBuffer, int &tabCount)
{
  bool understood = false;
  outputBuffer << def_include;
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
          addTabs(outputBuffer,tabCount);
          outputBuffer << if_knr;
          addTabs(outputBuffer,tabCount);
          outputBuffer << end_if;
          understood = true;
        }

        else if (codingStyle == DEF)
        {
          addTabs(outputBuffer,tabCount);
          outputBuffer << if_default_part1;
          addTabs(outputBuffer,tabCount);
          outputBuffer << if_default_part2;
          addTabs(outputBuffer,tabCount);
          outputBuffer << end_if;   
          understood = true;
        }

        understood = true;
      }

      else if (currToken == "ONE")
      {
        addTabs(outputBuffer,tabCount);
        outputBuffer << if_one_line;
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
                    addTabs(outputBuffer,tabCount);
                    outputBuffer << else_if_knr;
                    addTabs(outputBuffer,tabCount);
                    outputBuffer << end_if;
                    understood = true;
        }

        else if (codingStyle == DEF)
        {
                    addTabs(outputBuffer,tabCount);
                    outputBuffer << else_if_default_part1;
                    addTabs(outputBuffer,tabCount);
                    outputBuffer << else_if_default_part2;
                    addTabs(outputBuffer,tabCount);
                    outputBuffer << end_if;     
                    understood = true;
        }

      }

      else if (currToken == "ONE")
      {
        outputBuffer << else_if_one_line;
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
          outputBuffer << else_knr;
          understood = true;
        }

        else if (codingStyle == DEF)
        {
          outputBuffer << else_default;
          understood = true;
        }

        understood = true;
      }

      else if (currToken == "ONE")
      {
        outputBuffer << else_one_line;
        understood = true;
      }
    }

    else if (currToken == "MAIN")
    {
      currToken = file.getNextToken();
      if (mainDeclared) return false;
      
      if (currToken == "ARG")
      {
        if (codingStyle == KNR)
        {
          outputBuffer << arg_main_knr;
          understood = true;
        }

        else if (codingStyle == DEF)
        {
          outputBuffer << arg_main_default;
          understood = true;
        }

        understood = true;
      }

      else if (currToken == "VOID")
      {
        if (codingStyle == KNR)
        {
          outputBuffer << void_main_knr;
          understood = true;
        }

        else if (codingStyle == DEF)
        {
          outputBuffer << void_main_default;
          understood = true;
        }

        understood = true;
      }
    }

    else if (currToken == "FUNC")
    {
      currToken = file.getNextToken();
      if (inFunction) return false;
      inFunction = true;
      
      if (currToken == "VOID")
      {
        outputBuffer << type_void;
        outputBuffer << func_ident;
        outputBuffer << numFunctions;
        outputBuffer << "()";

        if (codingStyle == KNR)
        {
          outputBuffer << begin_func_knr;
          understood = true;
        }

        else if (codingStyle == DEF)
        {
          outputBuffer << begin_func_default;
          understood = true;
        }

      }

      else if (currToken == "INT")
      {
        outputBuffer << type_int;
        outputBuffer << func_ident;
        outputBuffer << numFunctions;
        outputBuffer << "()";

        if (codingStyle == KNR)
        {
          outputBuffer << begin_func_knr;
          understood = true;
        }

        else if (codingStyle == DEF)
        {
          outputBuffer << begin_func_default;
          understood = true;
        }

      }

      else if (currToken == "CHAR")
      {
        outputBuffer << type_char;
        outputBuffer << func_ident;
        outputBuffer << numFunctions;
        outputBuffer << "()";

        if (codingStyle == KNR)
        {
          outputBuffer << begin_func_knr;
          understood = true;
        }

        else if (codingStyle == DEF)
        {
          outputBuffer << begin_func_default;
          understood = true;
        }

      }

      else if (currToken == "FLOAT")
      {
        outputBuffer << type_float;
        outputBuffer << func_ident;
        outputBuffer << numFunctions;
        outputBuffer << "()";

        if (codingStyle == KNR)
        {
          outputBuffer << begin_func_knr;
          understood = true;
        }

        else if (codingStyle == DEF)
        {
          outputBuffer << begin_func_default;
          understood = true;
        }
      }


      else if (currToken == "DOUBLE")
      {
        outputBuffer << type_double;
        outputBuffer << func_ident;
        outputBuffer << numFunctions;
        outputBuffer << "()";

        if (codingStyle == KNR)
        {
          outputBuffer << begin_func_knr;
          understood = true;
        }

        else if (codingStyle == DEF)
        {
          outputBuffer << begin_func_default;
          understood = true;
        }
      }
      tabCount++;
      numFunctions++;
    }

    else if (currToken == "ENDFUNC")
    {
      if (!inFunction) return false;
      inFunction = false;   
      outputBuffer << end_func;
      tabCount--;
      understood = true;
      // numFunctions--;
    }

    if (!understood) return false;
  }

  return understood;
}

void error(bool retval, readFile &file)
{
  if(!retval)
  {
    string errToken = file.getPrevToken();
    int currLine  = file.getLineNo();

    cout << "ERROR @ line " << currLine << endl;
    cout << "Token: "       << errToken << endl;

    exit(1);
  }
}

int main(int argc, char* argv[])
{
  cout << "--------ccgen: A lightweight boilerplate C generator--------" << endl;
  cout << "---------------------Version 0.0.2--------------------------" << endl;

  stringstream outputBuffer;
  int tabCount = 0;
  if (argc < 3)
  {
    cout << "ERROR: No input Arguments Specified" << endl;
    usage();
  }

  readFile file(argv[1]);
  cout << "Reading file..." << endl;
  file.getContents();
  usleep(300000);
  cout << "File Read Succesful." << endl;
  usleep(300000);
  cout << "Parsing file..." << endl;
  usleep(300000);
  bool retval = parseTokens(file,outputBuffer,tabCount);
  error(retval,file);
  cout << "DONE" << endl;
  // cout << "parse = "<< boolalpha << retval << endl;
  string currentStructure;
  ofstream o(argv[2]);



  currentStructure = outputBuffer.str();
  o << currentStructure;


  return retval;
}