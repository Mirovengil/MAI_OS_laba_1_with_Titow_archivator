#include "TParser.h"
#include <iostream>

TParser::TParser()
{
    dictionary.resize(0);
    dictionary.push_back({"ls", 0, LS});                // показать текущую папку
    dictionary.push_back({"ls", 1, LS_TARGET});         // показать указанную папку
    dictionary.push_back({"cat", INF, CAT});            // вывести на экран указанные файлы
    dictionary.push_back({"nice", 0, NICE_ME});         // показать приоритет текущего процесса
    dictionary.push_back({"nice", 3, NICE_SMB});        // запустить процесс с указанным приоритетом
    dictionary.push_back({"exit", 0, FINISH_PROGRAM});  // выйти из терминала
    dictionary.push_back({"exit", 1, EXIT_SMB});        // убить i-ый дочерний процесс
    dictionary.push_back({"killall", 1, KILLALL});         // убить процесс по имени
    dictionary.push_back({"unknown", 1, UNKNOWN});         // убить процесс по имени
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
            return;
        }        
        return;
    }
};

void TParser::parseCmd(std::string cmd)
{
    inputString = cmd; 
}

int TParser::getNumberOfWords()
{
    int numberOfWords = 1;
    for (int i = 0; i < inputString.size(); ++i)
        numberOfWords += (inputString[i] == ' ');
    
    return numberOfWords;
}

int TParser::getIndexInDictionary(std::string cmd, int paramsNumber)
{
    for (int i = 0; i < dictionary.size(); ++i)
    {
        if (dictionary[i].text == cmd && dictionary[i].numberOfParams == paramsNumber)
            return i;    
    }
    return dictionary.size()-1;
};

CommandCode TParser::getCmdCode()
{
    int numberOfWords = getNumberOfWords();
    
    parseWord(0);
    std::string firstWord = targetWord;

    int indexInDictionary = getIndexInDictionary(firstWord, numberOfWords-1);
    return dictionary[indexInDictionary].code;
}

std::vector <std::string> TParser::getParams()
{
    std::vector <std::string> params;
    params.resize(0);

    for (int i = 0; i < getNumberOfWords()-1; ++i)
    {
        parseWord(i + 1);
        params.push_back(targetWord);
    }

    return params;
}
