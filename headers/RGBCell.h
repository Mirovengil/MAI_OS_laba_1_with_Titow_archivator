#ifndef RGBCELL_H
#define RGBCELL_H

#include <cstdint>

class RGBCell
{
private:
    uint8_t _redColor;
    uint8_t _greenColor;
    uint8_t _blueColor;
public:
    RGBCell(uint8_t r, uint8_t g, uint8_t b);
    RGBCell();
    uint8_t getRedValue();
    uint8_t getGreenValue();
    uint8_t getBlueValue();

    void setRedValue(uint8_t value);
    void setGreenValue(uint8_t value);
    void setBlueValue(uint8_t value);
};

#endif //RGBCELL_H
