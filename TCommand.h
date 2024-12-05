#ifndef TCOMMAND_H
#define TCOMMAND_H

#include <string>

enum CommandCode
{
    LS,
    LS_TARGET,
    CAT,
    NICE_ME,
    NICE_SMB,
    EXIT_SMB,
    FINISH_PROGRAM,
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