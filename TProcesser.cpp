#include <stdio.h>
#include <stdlib.h>
#include "TProcesser.h"
#include <iostream>
#include <filesystem>
#include <fstream>

std::vector<std::string> TProcesser::getLsCommandResult()
{
    std::vector <std::string> out;

    std::filesystem::path currentDir = std::filesystem::current_path();
    std::string currentDirStr = currentDir;

    out.push_back("Директория: " + currentDirStr);     // директория
                                            
                                            // все файлы директории -- подряд
    out.push_back("Список файлов:");
    
    std::string tabulations = "\t\t";
    for (auto &fileIterator : std::filesystem::directory_iterator(currentDir))
    {    
        std::string filename = fileIterator.path().filename(); 
        out.push_back(tabulations + filename);
    }

    return out; 
}

std::vector<std::string> TProcesser::getLsCommandResult(std::string directory)
{
    std::vector <std::string> out;

    try
    {
        out.push_back("Директория: " + directory + "/");     // директория
                                                
                                                // все файлы директории -- подряд
        out.push_back("Список файлов:");
        
        std::string tabulations = "\t\t";
        for (auto &fileIterator : std::filesystem::directory_iterator(directory))
        {    
            std::string filename = fileIterator.path().filename(); 
            out.push_back(tabulations + filename);
        }
    }
    catch(...)
    {
        out.resize(0);
        out.push_back("Возникли проблемы с открытием указаной папки!");
    }

    return out; 
}

std::vector<std::string> TProcesser::getCatCommandResult(std::vector<std::string>params)
{
    std::vector <std::string> out;

    // проверка, что все файлы существуют
    for (auto it : params)
    {
        if (!std::filesystem::exists(it))
        {
            out.push_back("Часть указанных файлов не найдена!!");
            return out;
        }
    }

    // считывание содержимого файлов
    out.push_back("Содержимое файлов:\n");
    std::string line;
    std::string tabulations = "\t\t";

    for (auto it : params)
    {
        // подпись: "имя файла"
        out.push_back("Файл: " + it);
        std::ifstream fIn(it);

        // содержимое файла подряд
        while (std::getline(fIn, line))
        {
            out.push_back(tabulations + line);
        }
        fIn.close();
        out.push_back("\n");
    }
    return out;
}

std::vector<std::string> TProcesser::getNiceCommandResult()
{
    std::vector <std::string> out;
    
    std::string result = "Приоритет текущего процесса: ";

    int priority = processesWorker.getCurrentPriority();
    if (priority == TProcessesWorker::BAD_PRIORITY)
    {
        out.push_back("Возникла ошибка!");
        return out;
    }

    std::string priorityCorrectValue = std::to_string(priority);
    out.push_back(result + priorityCorrectValue);
    return out;
}