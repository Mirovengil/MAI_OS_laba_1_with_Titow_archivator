#include "TBytesArray.h"
#include <stdio.h>
#include <string.h>
#include <stdexcept>
#include <iostream>

TBytesArray::TBytesArray(int size)
{
    this->size = size;
    data = (char*)malloc(sizeof(char) * size);
}


TBytesArray::~TBytesArray()
{
    free(data);
}

TBytesArray::TBytesArray(TBytesArray &other)
{
    size = other.size;
    data = (char*)malloc(size * sizeof(char));
    memcpy(data, other.data, size);
}


int TBytesArray::getSize()
{
    return size;
}


char* TBytesArray::getCharPtr()
{
    return data;
}


std::string TBytesArray::getAsString()
{
    std::string result = "";
    for (int i = 0; i < size; ++i)
        result = result + data[i];
    return result;
}

void TBytesArray::setChar(int index, char value)
{
    checkIndex(index);
    data[index] = value;
}

char TBytesArray::getChar(int index)
{
    checkIndex(index);
    return data[index];
}

void TBytesArray::checkIndex(int i)
{
    if (i >= size)
        throw std::range_error("TBytesArray : out of array!");
}

