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
        std::cout << "I don't know command\"" << currentCmd << "\"!\n";
        std::cout << "But I'll try to make it by cmd system()\n";
        processer.makeCommandBySystem(currentCmd);
    }
}
