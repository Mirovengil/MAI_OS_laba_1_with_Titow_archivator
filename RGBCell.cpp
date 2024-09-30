#include "RGBCell.h"

RGBCell::RGBCell()
{
    _redColor = 0;
    _greenColor = 0;
    _blueColor = 0;
};

RGBCell::RGBCell(int r, int g, int b)
{
    _redColor = r;
    _greenColor = g;
    _blueColor = b;
};

int RGBCell::getRedValue()
{
    return _redColor;
};

int RGBCell::getGreenValue()
{
    return _greenColor;
};

int RGBCell::getBlueValue()
{
    return _blueColor;
};

void RGBCell::setRedValue(int value)
{
    _redColor = value;
};

void RGBCell::setGreenValue(int value)
{
    _greenColor = value;
};

void RGBCell::setBlueValue(int value)
{
    _blueColor = value;
};
