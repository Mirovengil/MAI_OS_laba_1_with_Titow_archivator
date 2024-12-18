#include "TProcessesWorker.h"
#include <sys/resource.h>
#include <sys/types.h>
#include <unistd.h>
#include <cerrno>
#include <signal.h>

int TProcessesWorker::getCurrentPriority()
{
    id_t currentPID = getpid(); 
    int param = PRIO_PROCESS;
    int priority = getpriority(param, currentPID);
    
    if (priority == -1 && errno != 0)
        return BAD_PRIORITY;

    return priority;
}

bool TProcessesWorker::startProcess(std::string name, int priority)
{
}
