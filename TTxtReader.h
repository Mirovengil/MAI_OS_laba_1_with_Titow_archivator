#ifndef TTXTPARSER_H
#define TTXTPARSER_H

#include "TMessage.h"
#include <string>

class TTxtReader
{
    bool opened;
    char *buffer;

    long currentByteIndex;
    long numberOfBytes;
public:
    TTxtReader();
    void openFile(std::string filename);
    TMessage readMessage();
    void closeFile();
    bool fileIsFinished(); 
    int getNumberOfMessages();
    int getSizeInBytes();
};

#endif  //TTXTPARSER_H