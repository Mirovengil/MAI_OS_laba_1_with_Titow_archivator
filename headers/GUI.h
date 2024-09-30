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

class MyGUI : public QWidget
{
private:
    QVBoxLayout *_layoutMain;
    QPushButton *_btnSelectImage;
    QPushButton *_btnUseSobelsFilter;
    QLabel *_lblImagePreview;
    QPixmap *_pixmapImageLoader;
    QLabel *_lblNumberOfThreads;
    QSlider *_sliderNumberOfThreads;
    QMessageBox *_messageBoxTimesResult;
    QFileDialog *_fileDialogForSelectImageFile;

    int _numberOfThreads;
public slots:
    void renewNumberOfThreads();
    void makeProcessing();

public:
    MyGUI();
    ~MyGUI();
};

#endif // GUI_H