#include "TBytesArrayFiller.h"
#include <string.h>

TBytesArrayFiller::TBytesArrayFiller(TBytesArray *array)
{
    indexOfCurrentByte = 0;
    this->array = array;
}

void TBytesArrayFiller::fillWithMessage(TMessage message)
{
    int numberOfBytesToCopy;
    if (indexOfCurrentByte + TMessage::messageSize >= array->getSize())
        numberOfBytesToCopy = array->getSize() - indexOfCurrentByte;
    else
        numberOfBytesToCopy = TMessage::messageSize;

    memcpy(array->getCharPtr() + indexOfCurrentByte, message.getMessage(), numberOfBytesToCopy);
    indexOfCurrentByte += numberOfBytesToCopy;
}
