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

    int (*_functorOfLuminocity)(RGBCell);
    int (*_functorOfPow2)(int);
    int (*_functorOfSqrt)(int);

    int _startLine;
    int _endLine;

    bool _processLeftBorder;
    bool _processRightBorder;
public:
    MyThread(); // сильно много параметров, поэтому -- пустой конструктор + сеттеры
    void run(); // здесь происходит вся основная обработка
    void reset();

    // сеттеры входных данных
    void setOrigMatrix(ImageMatrix *m);
    void setMatrixOfLuminocity(Matrix *m);
    void setMatrixOfXYConvolution(Matrix *mx, Matrix *my);
    void setResultImageMatrix(ImageMatrix *m);
    void setFunctorOfLuminocity(int (*f)(RGBCell));
    void setFunctorOfPow2(int (*f)(int));
    void setFunctorOfSqrt(int (*f)(int));
    void setLines(int start, int end);
    void setBordersProcessing(bool left, bool right);
};

#endif// MY_THREAD_H