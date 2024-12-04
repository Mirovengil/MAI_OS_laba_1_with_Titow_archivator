#ifndef TBYTESARRAYFILLER_H
#define TBYTESARRAYFILLER_H

#include "TBytesArray.h"
#include "TMessage.h"

class TBytesArrayFiller
{
private:
    int indexOfCurrentByte;
    TBytesArray *array;
public:
    TBytesArrayFiller(TBytesArray *array);
    void fillWithMessage(TMessage message);
};

#endif //TBYTESARRAYFILLER_H