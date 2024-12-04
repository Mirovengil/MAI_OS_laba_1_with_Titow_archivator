#include "TTxtWriter.h"

void TTxtWriter::open(std::string filename)
{
    fOut.open(filename);
}

void TTxtWriter::write(TBytesArray data)
{
    for (int i = 0; i < data.getSize(); ++i)
        fOut << data.getChar(i);
}

void TTxtWriter::close()
{
    fOut.close();
}
