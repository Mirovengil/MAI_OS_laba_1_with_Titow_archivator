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
    int getCurrentPriority();
    bool startProcess(std::string name, int priority);
    static const int BAD_PRIORITY = 7777; 

    int getNumberOfProcesses();
    std::pair<pid_t, std::string> getProcess(int index);
    void popProcess();
};

#endif// PROCESSES_WORKER_H