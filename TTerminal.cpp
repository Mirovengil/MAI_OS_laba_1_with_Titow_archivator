#include "TTerminal.h"
#include <iostream>

const std::string invitationForInput = "> ";

TTerminal::TTerminal()
{
    std::cout << "Здравствуй, путник!!\n";
    std::cout << "Я есмь терминал by IVAN_IV...\n";
}

void TTerminal::inputCmd()
{
    std::cout << invitationForInput;
    std::getline(std::cin, currentCmd);
}

TTerminal::~TTerminal()
{
    std::cout << "Спасибо за использование терминала by_IVAN_IV...\n";
    std::cout << "Удачи, путник!\n";
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
        std::cout << "Я не знаю команды \"" << currentCmd << "\"!\n";
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
        auto params = parser.getParams();
        auto out = processer.getCatCommandResult(params);
        for (auto it : out)
            std::cout << it << "\n";
    }
    if (parser.getCmdCode() == NICE_ME)
    {
        auto out = processer.getNiceCommandResult();
        for (auto it : out)
            std::cout << it << "\n";        
    }
    if (parser.getCmdCode() == NICE_SMB)
    {
        auto params = parser.getParams();
        auto out = processer.getNiceCommandResult(params);
        for (auto it : out)
            std::cout << it << "\n";        
    }
    if (parser.getCmdCode() == EXIT_SMB)
    {
        
    }
    if (parser.getCmdCode() == FINISH_PROGRAM)
    {
        isRunning = false;
    }
    if (parser.getCmdCode() == KILLALL)
    {
        
    }
}
