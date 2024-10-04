#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QSlider>
#include <QMessageBox>
#include <QFileDialog>
#include <QString>
#include <QImage>
#include "ImageMatrix.h"
#include <vector>
#include <QElapsedTimer>
#include "MyThread.h"

class MyGUI : public QWidget
{
private:
    QGridLayout *_layoutMain;
    QVBoxLayout *_layoutOfProcessingElems;
    QVBoxLayout *_layoutOfImageElems;
    QPushButton *_btnSelectImage;
    QPushButton *_btnUseSobelsFilter;
    QLabel *_lblImagePreview;
    QPixmap *_pixmapImageLoader;
    QImage *_imageForProcessing;
    QLabel *_lblNumberOfThreads;
    QSlider *_sliderNumberOfThreads;
    QMessageBox *_messageBoxTimesResult;
    QFileDialog *_fileDialogForLoadImageFile;
    QPushButton *_btnReset;
    ImageMatrix *_imageMatrix;
    QElapsedTimer *_timerOfProcessing;
    QPushButton *_btnSaveImage;

    int _numberOfThreads;
    std::vector <MyThread*> _threads;

    void _openImage(QString filename);

public slots:
    void renewNumberOfThreads();
    void makeProcessing();
    void loadImageFromFile();
    void resetImageToNonFiltered();
    void saveImageToFile();
public:
    MyGUI();
    ~MyGUI();
};

#endif // GUI_H