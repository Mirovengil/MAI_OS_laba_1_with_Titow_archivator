#include <stdio.h>
#include <stdlib.h>
#include "TProcesser.h"
#include <iostream>
#include <filesystem>

std::vector<std::string> TProcesser::getLsCommandResult()
{
    std::vector <std::string> out;

    std::filesystem::path currentDir = std::filesystem::current_path();
    std::string currentDirStr = currentDir;

    out.push_back("Директория: " + currentDirStr);     // директория
                                            
                                            // все файлы директории -- подряд
    out.push_back("Files list:");
    
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
        out.push_back("Files list:");
        
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

