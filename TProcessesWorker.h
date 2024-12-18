#ifndef PROCESSES_WORKER_H
#define PROCESSES_WORKER_H

#include <iostream>
#include <vector>
#include <sys/types.h>

class TProcessesWorker
{
private:
    std::vector <std::pair<pid_t, std::string>> openedProcesses;
public:
    static const int BAD_PRIORITY = 7777; 
    
    int getCurrentPriority();
    bool startProcess(std::string name, int priority);
    bool closeProcess(int index);

    int getNumberOfProcesses();
    std::pair<pid_t, std::string> getProcess(int index);
    void popProcess();
};

#endif// PROCESSES_WORKER_H