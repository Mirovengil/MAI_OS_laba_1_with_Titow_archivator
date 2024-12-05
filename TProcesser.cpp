#include <stdio.h>
#include <stdlib.h>
#include "TProcesser.h"
#include <iostream>

void TProcesser::makeCommandBySystem(std::string command)
{
    std::cout << "system(\"" << command << "\")\n";
    system(command.c_str());
}
