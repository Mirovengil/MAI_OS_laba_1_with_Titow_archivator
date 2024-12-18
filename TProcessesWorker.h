#ifndef PROCESSES_WORKER_H
#define PROCESSES_WORKER_H

#include <iostream>

class TProcessesWorker
{
private:
public:
    int getCurrentPriority();
    bool startProcess(std::string name, int priority);
    static const int BAD_PRIORITY = 7777; 
};

#endif// PROCESSES_WORKER_H