#include "TProcessesWorker.h"
#include <vector>
#include <sys/resource.h>
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
    pid_t child_pid = fork();
    if (child_pid == -1)
        return false;

    if (child_pid == 0)
    {
        // дочерний процесс
        if (setpriority(PRIO_PROCESS, child_pid, priority) == -1)
            return false;
        
        std::vector <char*> argv;
        argv.push_back(const_cast<char*>(name.c_str()));
        // что бы мы не запускали -- запустим это без аргументов...
        argv.push_back(nullptr);

        if (execvp(name.c_str(), argv.data()) == -1)
            return false;
        
        openedProcesses.push_back({child_pid, name});
    }

    return true;
}

int TProcessesWorker::getNumberOfProcesses()
{
    return openedProcesses.size();
}

std::pair<pid_t, std::string> TProcessesWorker::getProcess(int index)
{
    return openedProcesses[index];
}
