#include "MyThread.h"

MyThread::MyThread()
{
    this->reset();
}

void MyThread::run()
{
    _matrixOfLuminocity->fillWithImageMatrix(*_origMatrix, _functorOfLuminocity, _startLine, _endLine);

    _matrixOfLuminocity->doConvolution(SobelsMatrixX, *_matrixOfXConvolution, _startLine+1, _endLine+1);
    _matrixOfLuminocity->doConvolution(SobelsMatrixY, *_matrixOfYConvolution, _startLine-1, _endLine-1);

    _matrixOfXConvolution->useFunctionToCells(_functorOfPow2, _startLine, _endLine);
    _matrixOfYConvolution->useFunctionToCells(_functorOfPow2, _startLine, _endLine);
    
    // все оставшиеся вычисления провожу с _matrixOfXConvolution
    _matrixOfXConvolution->summWith(*_matrixOfXConvolution, _startLine, _endLine);
    _matrixOfXConvolution->useFunctionToCells(_functorOfSqrt, _startLine, _endLine);
    _matrixOfXConvolution->convertToImageMatrix(*_resultImageMatrix, _startLine, _endLine);
    _resultImageMatrix->convertToImage(*_resultImage, _startLine, _endLine);
}

void MyThread::reset()
{
    _origMatrix = nullptr;
    _matrixOfLuminocity = nullptr;;
    _matrixOfXConvolution = nullptr;
    _matrixOfYConvolution = nullptr;
    _resultImageMatrix = nullptr;
    _resultImage = nullptr;

    _functorOfLuminocity = nullptr;
    _functorOfPow2 = nullptr;
    _functorOfSqrt = nullptr;

    _startLine = -1;
    _endLine = -1;
};

void MyThread::setOrigMatrix(ImageMatrix *m)
{
    _origMatrix = m;
}

void MyThread::setMatrixOfLuminocity(Matrix *m)
{
    _matrixOfLuminocity = m;
}

void MyThread::setMatrixOfXYConvolution(Matrix *mx, Matrix *my)
{
    _matrixOfXConvolution = mx;
    _matrixOfYConvolution = my;
}

void MyThread::setResultImageMatrix(ImageMatrix *m)
{
    _resultImageMatrix = m;
}

void MyThread::setResultImage(QImage *m)
{
    _resultImage = m;
}

void MyThread::setFunctorOfLuminocity(int (*f)(RGBCell))
{
    _functorOfLuminocity = f;
}

void MyThread::setFunctorOfPow2(int (*f)(int))
{
    _functorOfPow2 = f;
}

void MyThread::setFunctorOfSqrt(int (*f)(int))
{
    _functorOfSqrt = f;
}

void MyThread::setLines(int start, int end)
{
    _startLine = start;
    _endLine = end;
};
