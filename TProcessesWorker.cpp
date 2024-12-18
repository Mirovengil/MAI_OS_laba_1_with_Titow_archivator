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
        
    }
    openedProcesses.push_back({child_pid, name});

    return true;
}

void TProcessesWorker::popProcess()
{
    openedProcesses.pop_back();
}

bool TProcessesWorker::closeProcess(int index)
{
    id_t PID = openedProcesses[index].first;
    if (kill(PID, SIGKILL) == -1)
        return false;
    
    openedProcesses[index] = openedProcesses[openedProcesses.size() - 1];
    popProcess();

    return true;
}

bool TProcessesWorker::closeProcess(std::string name)
{
    for (int i = 0; i < openedProcesses.size(); ++i)
    {
        if (openedProcesses[i].second == name)
            return closeProcess(i);
    }
    return false;
}


int TProcessesWorker::getNumberOfProcesses()
{
    return openedProcesses.size();
}

std::pair<pid_t, std::string> TProcessesWorker::getProcess(int index)
{
    return openedProcesses[index];
}
