#ifndef TPROCESSER_H
#define TPROCESSER_H

#include "TProcessesWorker.h"
#include <string>
#include <vector>

class TProcesser
{
private:
    TProcessesWorker processesWorker;
public:
    std::vector<std::string> getLsCommandResult();
    std::vector<std::string> getLsCommandResult(std::string directory);
    std::vector<std::string> getCatCommandResult(std::vector<std::string>params);
    std::vector<std::string> getNiceCommandResult();
    std::vector<std::string> getNiceCommandResult(std::vector<std::string>params);
    std::vector<std::string> getSonslistCommandResult();
    std::vector<std::string> getExitCommandResult(std::vector<std::string> params);
    std::vector<std::string> getKillallCommandResult(std::vector<std::string> params);
};

#endif //TPROCESSER_H