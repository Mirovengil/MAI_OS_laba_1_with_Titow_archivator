#ifndef PROCESSES_WORKER_H
#define PROCESSES_WORKER_H

class TProcessesWorker
{
private:
public:
    int getCurrentPriority();

    static const int BAD_PRIORITY = 7777; 
};

#endif// PROCESSES_WORKER_H