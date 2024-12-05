#ifndef TTERMINAL_H
#define TTERMINAL_H

#include <string>
#include "TParser.h"
#include "TProcesser.h"

class TTerminal
{
private:
    bool isRunning;
    std::string currentCmd;
    TParser parser;
    TProcesser processer;

    void inputCmd();
    void parseCmd();
public:
    TTerminal();
    ~TTerminal();
    void exec();
};

#endif //TTERMINAL_H