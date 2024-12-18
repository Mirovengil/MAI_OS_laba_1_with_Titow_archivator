#ifndef TPARSER_H
#define TPARSER_H

#include <vector>
#include <string>
#include "TCommand.h"

class TParser
{
private:
    std::vector <TCommand> dictionary;

    std::string inputString;
    std::string targetWord;

    void parseWord(int wordIndex);
    int getNumberOfWords();
public:
    TParser();
    void parseCmd(std::string cmd);
    CommandCode getCmdCode();
    int getIndexInDictionary(std::string cmd, int paramsNumber);
    std::vector <std::string> getParams();
};

#endif //TPARSER_H