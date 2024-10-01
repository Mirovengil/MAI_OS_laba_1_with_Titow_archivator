#include "ImageMatrix.h"

int ImageMatrix::getN()
{
    return _data.size();
};
int ImageMatrix::getM()
{
    return _data[0].size();
};

ImageMatrix::ImageMatrix(QImage *image)
{
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

RGBCell ImageMatrix::getRGBValue(int i, int j)
{
    return _data[i][j];
};

// void ImageMatrix::doConvolution(const TCore *with)
// {
//     for (int i = 1; i < _data.size()-1; ++i)
//     {
//         for (int j = 1; j < _data[i].size(); ++j)
//         {
//             int buffer = 0;

//         }
//     }
// };
