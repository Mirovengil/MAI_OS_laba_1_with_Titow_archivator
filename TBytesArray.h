#ifndef TBYTESARRAY_H
#define TBYTESARRAY_H

#include <string>

class TBytesArray
{
private:
    char *data;
    int size;
    void checkIndex(int i);
public:
    TBytesArray(int size);
    TBytesArray(TBytesArray &other);
    ~TBytesArray();
    int getSize();
    char* getCharPtr();
    void setChar(int index, char value);
    char getChar(int index);
    std::string getAsString();
};

#endif  //TBYTESARRAY_H