#include "TTerminal.h"
#include <iostream>

const std::string invitationForInput = "> ";

TTerminal::TTerminal()
{
    std::cout << "Hello, traveller!\n";
    std::cout << "I'm the terminal by IVAN_IV\n";
}

void TTerminal::inputCmd()
{
    std::cout << invitationForInput;
    std::getline(std::cin, currentCmd);
}

TTerminal::~TTerminal()
{
    std::cout << "Thank you for using me!\n";
    std::cout << "Good luck you, traveller!\n";
}

void TTerminal::exec()
{
    isRunning = true;

    while (isRunning)
    {
        inputCmd();
        parseCmd();
    }
}

void TTerminal::parseCmd()
{
    parser.parseCmd(currentCmd);
    if (parser.getCmdCode() == UNKNOWN)
    {
        std::cout << "I don't know command \"" << currentCmd << "\"!\n";
    }
    if (parser.getCmdCode() == LS)
    {
        auto out = processer.getLsCommandResult();
        for (auto it : out)
            std::cout << it << "\n";
    }
    if (parser.getCmdCode() == LS_TARGET)
    {
        auto params = parser.getParams();
        auto out = processer.getLsCommandResult(params[0]);
        for (auto it : out)
            std::cout << it << "\n";
    }
    if (parser.getCmdCode() == CAT)
    {
        
    }
    if (parser.getCmdCode() == NICE_ME)
    {
        
    }
    if (parser.getCmdCode() == NICE_SMB)
    {
        
    }
    if (parser.getCmdCode() == EXIT_SMB)
    {
        
    }
    if (parser.getCmdCode() == FINISH_PROGRAM)
    {
        
    }
    if (parser.getCmdCode() == KILLALL)
    {
        
    }
}
