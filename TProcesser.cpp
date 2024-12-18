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

std::vector<std::string> TProcesser::getNiceCommandResult(std::vector<std::string>params)
{
    std::vector <std::string> out;


    std::string processName = params[0];
    int priority = std::atoi(params[1].c_str());
    if (!processesWorker.startProcess(processName, priority))
        out.push_back("При запуске указанного процесса возникли проблемы!");

    if (priority > 19)
    {
        out.push_back("Возможность задавать приоритет больше, чем число 19, отсутствует.");
        out.push_back("Приоритет запущенного процесса равен: 19.");
    }
    return out;
}

std::vector<std::string> TProcesser::getSonslistCommandResult()
{
    std::vector <std::string> out;

    int N = processesWorker.getNumberOfProcesses();
    out.push_back("Число дочерних процессов: " + std::to_string(N));

    std::string tabulations = "\t\t";
    for (int i = 0; i < N; ++i)
    {
        auto process = processesWorker.getProcess(i);

        std::string PID = std::to_string(static_cast<int>(process.first));
        std::string processName = process.second;

        out.push_back(tabulations + PID + ". " + processName);
    }

    return out;
}
