#include "TCryptographer.h"
#include <iostream>

TBytesArray TCryptographer::doCrypto(TBytesArray a, TBytesArray b)
{
    setLongAndShortData(&a, &b);
    TBytesArray result(longData->getSize());

    for (int i = 0; i < longData->getSize(); ++i)
    {
        char firstSymbol, secondSymbol, resultSymbol;
        // std::cout << "i: " << firstSymbol << " " << secondSymbol << "\n"; // TODO : kill me
        firstSymbol = longData->getChar(i);
        secondSymbol = shortData->getChar(i % shortData->getSize());
        resultSymbol = firstSymbol ^ secondSymbol;

        result.setChar(i, resultSymbol);
    }

    return result;
}

void TCryptographer::setLongAndShortData(TBytesArray *a, TBytesArray *b)
{
    if (a->getSize() > b->getSize())
    {
        shortData = b;
        longData = a;
    }
    else
    {
        longData = b;
        shortData = a;
    }
}