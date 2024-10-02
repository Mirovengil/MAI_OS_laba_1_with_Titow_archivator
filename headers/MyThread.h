#ifndef MY_THREAD_H
#define MY_THREAD_H

#include <QThread>
#include <QImage>
#include "Matrix.h"
#include "ImageMatrix.h"

class MyThread : public QThread
{
private:
    ImageMatrix *_origMatrix;
    Matrix *_matrixOfLuminocity;
    Matrix *_matrixOfXConvolution;
    Matrix *_matrixOfYConvolution;
    ImageMatrix *_resultImageMatrix;
    QImage *_resultImage;

    int (*_functorOfLuminocity)(RGBCell);
    int (*_functorOfPow2)(int);
    int (*_functorOfSqrt)(int);

    int _startLine;
    int _endLine;

public:
    MyThread(); // сильно много параметров, поэтому -- пустой конструктор + сеттеры
    void run(); // здесь происходит вся основная обработка
    void reset();
};

#endif// MY_THREAD_H