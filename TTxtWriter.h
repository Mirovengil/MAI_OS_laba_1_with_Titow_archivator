#ifndef TTXTWRITER_H
#define TTXTWRITER_H

#include "TBytesArray.h"
#include <fstream>

class TTxtWriter
{
private:
    std::ofstream fOut;
public:
    void open(std::string filename);
    void write(TBytesArray data);
    void close();
};

#endif //TTXTWRITER_H