#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "RGBCell.h"
#include <QImage>

class ImageMatrix
{
private:
    std::vector <std::vector <RGBCell>> _data;
public:
    ImageMatrix(QImage image);
};

#endif //MATRIX_H