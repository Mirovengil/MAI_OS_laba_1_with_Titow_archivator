#ifndef IMAGE_MATRIX_H
#define IMAGE_MATRIX_H

#include <vector>
#include "RGBCell.h"
#include <QImage>
#include "TCore.h"

class ImageMatrix
{
private:
    std::vector <std::vector <RGBCell>> _data;
public:
    ImageMatrix(QImage *image);
    ImageMatrix(int sizeN, int sizeM);
    int getN(); // число элементов по горизонтали
    int getM(); // число элементов по вертикали
    RGBCell getRGBValue(int i, int j);
    void setRGBValue(int i, int j, RGBCell value);
    void setRGBValue(int i, int j, uint8_t coeff);  // заполняет клетку серым цветом с указанным коэффициентом яркости

    // ф-ии для многопоточки
    void convertToImage(QImage &result,
        int startLine,  int endLine);
};

#endif //IMAGE_MATRIX_H