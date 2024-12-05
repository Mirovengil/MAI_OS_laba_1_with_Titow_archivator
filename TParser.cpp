#include "TParser.h"
#include <iostream>

TParser::TParser()
{
    dictionary.resize(0);
    dictionary.push_back({"ls", 0});            // показать текущую папку
    dictionary.push_back({"ls", 1});            // показать указанную папку
    dictionary.push_back({"cat", INF});         // вывести на экран указанные файлы
    dictionary.push_back({"nice", 0});          // показать приоритет текущего процесса
    dictionary.push_back({"nice", 3});          // запустить процесс с указанным приоритетом
    dictionary.push_back({"exit", 0});          // выйти из терминала
    dictionary.push_back({"exit", 1});          // убить i-ый дочерний процесс
    dictionary.push_back({"killall"});          // убить процесс по имени
}

bool TParser::cmdIsUnkonwn()
{
    parseWord(0);   
    return (!isInDictionary());
}

void TParser::parseWord(int wordIndex)
{
    targetWord = "";
    int currentWordIndex = 0;
    for (int i = 0; i < inputString.size(); ++i)
    {
        if (currentWordIndex < wordIndex)
        {
            if (inputString[i] == ' ')
                currentWordIndex++;

            continue;
        }

        for (int j = i; j < inputString.size(); ++j)
        {
            if (inputString[j] != ' ')
            {
                targetWord = targetWord + inputString[j];
                continue;
            }
        }        
        return;
    }
};

bool TParser::isInDictionary()
{
    std::cout << "word: " << targetWord << "\n";
    for (int i = 0; i < dictionary.size(); ++i)
        if (dictionary[i].text == targetWord)
            return true;

    return false;
}

void TParser::parseCmd(std::string cmd)
{
    inputString = cmd; 
}
