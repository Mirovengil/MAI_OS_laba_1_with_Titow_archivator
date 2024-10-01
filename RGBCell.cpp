#include "RGBCell.h"

uint8_t RGBCell::getLuminosity()
{
    uint8_t result = 0;
    result += static_cast<uint32_t>(0.299 * static_cast<double>(_redColor)); 
    result += static_cast<uint32_t>(0.587 * static_cast<double>(_greenColor)); 
    result += static_cast<uint32_t>(0.114 * static_cast<double>(_blueColor)); 

    return result;
};

RGBCell::RGBCell()
{
    _redColor = 0;
    _greenColor = 0;
    _blueColor = 0;
};

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

void RGBCell::setRedValue(uint8_t value)
{
    _redColor = value;
};

void RGBCell::setGreenValue(uint8_t value)
{
    _greenColor = value;
};

void RGBCell::setBlueValue(uint8_t value)
{
    _blueColor = value;
};
