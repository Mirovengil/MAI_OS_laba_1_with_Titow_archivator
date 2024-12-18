#ifndef TCOMMAND_H
#define TCOMMAND_H

#include <string>

enum CommandCode
{
    LS,                 // ГОТОВО
    LS_TARGET,          // ГОТОВО
    CAT,
    NICE_ME,            // ГОТОВО
    NICE_SMB,
    EXIT_SMB,
    FINISH_PROGRAM,     // ГОТОВО
    KILLALL,
    UNKNOWN,
};

const int INF = -1; // unlimited number of params
struct TCommand
{
    std::string text;
    int numberOfParams;
    CommandCode code;
};



#endif //TCOMMAND_H