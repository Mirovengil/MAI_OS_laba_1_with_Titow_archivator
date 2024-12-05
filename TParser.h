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
    bool isInDictionary();
public:
    TParser();
    void parseCmd(std::string cmd);
    bool cmdIsUnkonwn();
};

#endif //TPARSER_H