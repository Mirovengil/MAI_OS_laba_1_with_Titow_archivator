#ifndef TCRYPTOGRAPHER_H
#define TCRYPTOGRAPHER_H

#include "TBytesArray.h"

class TCryptographer
{
private:
    TBytesArray *longData;
    TBytesArray *shortData;

    void setLongAndShortData(TBytesArray *a, TBytesArray *b);
public:
    TBytesArray doCrypto(TBytesArray a, TBytesArray b);
};

#endif //TCRYPTOGRAPHER_H