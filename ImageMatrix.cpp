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
    QImage result(_data.size(), _data[0].size(), QImage::Format_RGB32);
    for (int i = 0; i < _data.size(); ++i)
        for (int j = 0; j < _data[i].size(); ++j)
        {

            int r = static_cast<int>(_data[i][j].getRedValue());
            int g = static_cast<int>(_data[i][j].getGreenValue());
            int b = static_cast<int>(_data[i][j].getBlueValue());
            QRgb value = qRgb(r, g, b);
            
            result.setPixel(i, j, value);
        }
    return result;
};

RGBCell ImageMatrix::getRGBValue(int i, int j)
{
    return _data[i][j];
};

void ImageMatrix::setRGBValue(int i, int j, RGBCell value)
{
    _data[i][j] = value;
};

void ImageMatrix::setRGBValue(int i, int j, uint8_t coeff)
{
    _data[i][j].setRedValue(coeff);
    _data[i][j].setGreenValue(coeff);
    _data[i][j].setBlueValue(coeff);
}; 

ImageMatrix::ImageMatrix(int sizeN, int sizeM)
{
    _data.resize(sizeN);
    for (int i = 0; i < sizeN; ++i)
    {
        _data[i].resize(sizeM);
        for (int j = 0; j < sizeM; ++j)
        {
            setRGBValue(i, j, 0);
        }
    }
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
