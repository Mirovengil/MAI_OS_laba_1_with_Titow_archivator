#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QSlider>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include "ImageMatrix.h"

class MyGUI : public QWidget
{
private:
    QVBoxLayout *_layoutMain;
    QPushButton *_btnSelectImage;
    QPushButton *_btnUseSobelsFilter;
    QLabel *_lblImagePreview;
    QPixmap *_pixmapImageLoader;
    QImage *_imageForProcessing;
    QLabel *_lblNumberOfThreads;
    QSlider *_sliderNumberOfThreads;
    QMessageBox *_messageBoxTimesResult;
    QFileDialog *_fileDialogForSelectImageFile;

    ImageMatrix *_imageMatrix;

    int _numberOfThreads;
    void _openImage(QString filename);

public slots:
    void renewNumberOfThreads();
    void makeProcessing();
    void selectImageFile();
public:
    MyGUI();
    ~MyGUI();
};

#endif // GUI_H