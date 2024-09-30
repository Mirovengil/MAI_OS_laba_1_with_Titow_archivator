#include "RGBCell.h"

RGBCell::RGBCell(uint8_t r, uint8_t g, uint8_t b)
{
    _redColor = r;
    _greenColor = g;
    _blueColor = b;
};

uint8_t RGBCell::getRedValue()
{
    return _redColor;
};

uint8_t RGBCell::getGreenValue()
{
    return _greenColor;
};

uint8_t RGBCell::getBlueValue()
{
    return _blueColor;
};
