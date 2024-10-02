#include "Matrix.h"

Matrix::Matrix()
{
    this->resize(0, 0);
};

Matrix::Matrix(int n, int m)
{
    this->resize(n, m);
};
    
void Matrix::resize(int n, int m)
{
    _data.resize(0);
    _data.resize(n);
    for (int i = 0; i < n; ++i)
    {
        _data[i].resize(m);
        for (int j = 0; j < m; ++j)
            _data[i][j] = 0;
    }
}

int Matrix::getValue(int i, int j)
{
    return _data[i][j];
};

void Matrix::setValue(int i, int j, int value)
{
    _data[i][j] = value;
};

Matrix::Matrix(ImageMatrix &source, int (*func)(RGBCell))
{
    this->resize(source.getN(), source.getM());
    for (int i = 0; i < _data.size(); ++i)
        for (int j = 0; j < _data[i].size(); ++j)
            _data[i][j] = func(source.getRGBValue(i, j));    
};

void Matrix::fillWithImageMatrix(ImageMatrix &source, int (*func)(RGBCell),
    int startLine, int endLine)
{
    for (int i = startLine; i < endLine; ++i)
        for (int j = 0; j < _data[i].size(); ++j)
            _data[i][j] = func(source.getRGBValue(i, j));    
};

void Matrix::doConvolution(const TCore &with)
{
    Matrix tmpMatrix(_data.size(), _data[0].size());

    for (int i = 1; i < _data.size()-1; ++i)
    {
        for (int j = 1; j < _data[i].size()-1; ++j)
        {
            
            for (int coreI = -1; coreI <= 1; ++coreI)
            {
                for (int coreJ = -1; coreJ <= 1; ++coreJ)
                {
                    tmpMatrix._data[i][j] += _data[i + coreI][j + coreJ] * with.getValue(coreI, coreJ);
                }
            }
        }
    }

    *this = tmpMatrix;
}; 

void Matrix::useFunctionToCells(int (*func)(int))
{
    for (int i = 0; i < _data.size(); ++i)
    {
        for (int j = 0; j < _data[i].size(); ++j)
        {
            _data[i][j] = func(_data[i][j]);
        }
    }
};

void Matrix::operator+=(Matrix &with)
{
    for (int i = 0; i < with._data.size(); ++i)
    {
        for (int j = 0; j < with._data[i].size(); ++j)
        {
            _data[i][j] += with._data[i][j];
        }
    }
};

ImageMatrix Matrix::convertToImageMatrix()
{
    ImageMatrix result(_data.size(), _data[0].size());
    for (int i = 0; i < _data.size(); ++i)
    {
        for (int j = 0; j < _data[i].size(); ++j)
        {
            result.setRGBValue(i, j, _data[i][j]);
        }
    }
    return result;
};