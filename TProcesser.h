#ifndef TPROCESSER_H
#define TPROCESSER_H

#include <string>
#include <vector>

class TProcesser
{
private:

public:
    std::vector<std::string> getLsCommandResult();
    std::vector<std::string> getLsCommandResult(std::string directory);
};

#endif //TPROCESSER_H