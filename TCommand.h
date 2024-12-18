#ifndef TCOMMAND_H
#define TCOMMAND_H

#include <string>

enum CommandCode
{
    LS,                 // ГОТОВО
    LS_TARGET,          // ГОТОВО
    CAT,                // ГОТОВО
    NICE_ME,            // ГОТОВО
    NICE_SMB,           // ГОТОВО
    EXIT_SMB,           // 
    FINISH_PROGRAM,     // ГОТОВО
    KILLALL,
    SONS_LIST,          // ГОТОВО
    UNKNOWN,            // ГОТОВО
};

const int INF = -1; // unlimited number of params
struct TCommand
{
    std::string text;
    int numberOfParams;
    CommandCode code;
};



#endif //TCOMMAND_H