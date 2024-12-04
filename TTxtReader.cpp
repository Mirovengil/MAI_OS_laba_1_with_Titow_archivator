#include "TTxtReader.h"
#include <string.h>
#include <stdexcept>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

TTxtReader::TTxtReader()
{
    opened = false;
}

void TTxtReader::openFile(std::string filename)
{
    if (opened)
        throw std::logic_error("TTxtReader : two files can't be opened simultaneously!");
    
    currentByteIndex = 0;

    // reads all file's bytes in variable "buffer"
    FILE *fIn;
    fIn = fopen(filename.c_str(), "rb");

    if (fIn == nullptr)
        throw std::logic_error("TTxtReader : can't open the file! (maybe it isn't exist?)");

    fseek (fIn, 0, SEEK_END);
    numberOfBytes = ftell(fIn);
    rewind(fIn);
    buffer = (char*)malloc(sizeof(char) * numberOfBytes);
    fread(buffer, numberOfBytes, 1, fIn);
    fclose(fIn);

    opened = true;
}

TMessage TTxtReader::readMessage()
{
    TMessage message;

    char messageText[TMessage::messageSize];
    
    int numberOfRemainingBytes = numberOfBytes - currentByteIndex;
    int numberOfBytesToRead;

    if (numberOfRemainingBytes < TMessage::messageSize)
        numberOfBytesToRead = numberOfRemainingBytes;
    else
        numberOfBytesToRead = TMessage::messageSize;

    memset(messageText, 0, TMessage::messageSize);
    memcpy(messageText, buffer+currentByteIndex, numberOfBytesToRead);
    currentByteIndex += numberOfBytesToRead;

    message.setMessage(messageText);

    return message;
}

void TTxtReader::closeFile()
{
    opened = false;
    free(buffer);
}

int TTxtReader::getNumberOfMessages()
{
    return (numberOfBytes / TMessage::messageSize) + 
        (numberOfBytes % TMessage::messageSize != 0);
};

bool TTxtReader::fileIsFinished()
{
    return (currentByteIndex == numberOfBytes);
} 

int TTxtReader::getSizeInBytes()
{
    return numberOfBytes;
};