#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include "RGBCell.h"
#include "ImageMatrix.h"
#include "TCore.h"

class Matrix
{
private:
    std::vector <std::vector <int>> _data;
public:
    Matrix();
    Matrix(int n, int m);
    Matrix(ImageMatrix &source, int (*func)(RGBCell));

    ImageMatrix convertToImageMatrix();
    void resize(int n, int m);
    int getValue(int i, int j);
    void setValue(int i, int j, int value);
    void useFunctionToCells(int (*func)(int));
    void operator+=(Matrix &with);

    // операции, которые следует отдавать разным потокам
    void fillWithImageMatrix(ImageMatrix &source, int (*func)(RGBCell),
        int startLine, int endLine);
    void doConvolution(const TCore &with, Matrix &resultMatrix,
        int startLine, int endLine);    
};

#endif// MATRIX_H