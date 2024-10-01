#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "RGBCell.h"
#include "ImageMatrix.h"

class Matrix
{
private:
    std::vector <std::vector <int>> _data;
public:
    Matrix();
    Matrix(int n, int m);
    Matrix(ImageMatrix &source, int (*func)(RGBCell));

    void resize(int n, int m);
    int getValue(int i, int j);
    void setValue(int i, int j, int value);
};

#endif// MATRIX_H