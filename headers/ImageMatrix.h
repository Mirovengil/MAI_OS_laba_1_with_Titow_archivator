#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "RGBCell.h"
#include <QImage>
#include "TCore.h"

class ImageMatrix
{
private:
    std::vector <std::vector <RGBCell>> _data;
public:
    ImageMatrix(QImage *image);
    QImage convertToImage();
    void doConvolution(const TCore *with);
};

#endif //MATRIX_H