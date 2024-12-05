#ifndef TCOMMAND_H
#define TCOMMAND_H

#include <string>

const int INF = -1; // unlimited number of params
struct TCommand
{
    std::string text;
    int numberOfParams;
};

#endif //TCOMMAND_H