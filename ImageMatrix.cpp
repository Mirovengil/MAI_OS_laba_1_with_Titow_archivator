#include "ImageMatrix.h"

ImageMatrix::ImageMatrix(QImage *image)
{
    // TODO : напиши конструктор от QT-шной картинки 
    int height = image->height();
    int width = image->width();

    _data.resize(width);
    for (int i = 0; i < width; ++i)
    {
        _data[i].resize(height);
        for (int j = 0; j < height; ++j)
        {
            QRgb pixelValue = image->pixel(i, j);
            _data[i][j].setRedValue(qRed(pixelValue));
            _data[i][j].setGreenValue(qGreen(pixelValue));
            _data[i][j].setBlueValue(qBlue(pixelValue));
        }
    }

};