#ifndef RGBCELL_H
#define RGBCELL_H

class RGBCell
{
private:
    int _redColor;
    int _greenColor;
    int _blueColor;
public:
    RGBCell(int r, int g, int b);
    RGBCell();
    int getRedValue();
    int getGreenValue();
    int getBlueValue();

    void setRedValue(int value);
    void setGreenValue(int value);
    void setBlueValue(int value);
};

#endif //RGBCELL_H
