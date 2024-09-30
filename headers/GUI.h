#ifndef GUI_H
#define GUI_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QSlider>

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

public:
    MyGUI();
    ~MyGUI();
};

#endif // GUI_H