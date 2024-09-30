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

QImage ImageMatrix::convertToImage()
{
    // TODO : реализуй ф-ю
    return QImage();
};

void ImageMatrix::doConvolution(const TCore *with)
{
    for (int i = 1; i < _data.size()-1; ++i)
    {
        for (int j = 1; j < _data[i].size(); ++j)
        {
            int buffer = 0;
            // интерсивность света: 0.299r + 0.587g + 0.114b
            // сумму -- пишу в ячейку
        }
    }
};
