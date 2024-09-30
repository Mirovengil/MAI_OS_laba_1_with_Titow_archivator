#include "GUI.h"
#include <QString>

const std::pair <int, int> _stdSizeOfGUIWindow = {1200, 800}; 
const std::pair <int, int> _stdSizeOfImageLabel = {1000, 600};
const int _stdValueOfSlider = 0;
const QString _sliderText = "Заданное число потоков: ";

MyGUI::MyGUI()
{
    this->resize(_stdSizeOfGUIWindow.first, _stdSizeOfGUIWindow.second);

    _pixmapImageLoader = new QPixmap;

    _layoutMain = new QVBoxLayout(this);
    
    _btnSelectImage = new QPushButton;
    _btnSelectImage->setText("Выбрать изображение для обработки");
    _layoutMain->addWidget(_btnSelectImage);
    
    _lblImagePreview = new QLabel("Здесь будет изображение");
    _pixmapImageLoader->load("../pic/picture_404.png");
    _lblImagePreview->setPixmap(*_pixmapImageLoader);
    _lblImagePreview->resize(_stdSizeOfImageLabel.first, _stdSizeOfImageLabel.second);
    _layoutMain->addWidget(_lblImagePreview);

    _lblNumberOfThreads = new QLabel(_sliderText + QString::number(_stdValueOfSlider));
    _layoutMain->addWidget(_lblNumberOfThreads);
    
    _sliderNumberOfThreads = new QSlider(Qt::Horizontal);
    _sliderNumberOfThreads->setMinimum(0);  // 2^0 = 1 поток
    _sliderNumberOfThreads->setMaximum(8);  // 2^8 = 256 потоков
    _sliderNumberOfThreads->setValue(_stdValueOfSlider);
    _layoutMain->addWidget(_sliderNumberOfThreads);

    _btnUseSobelsFilter = new QPushButton;
    _btnUseSobelsFilter->setText("Применить фильтр Собела");
    _layoutMain->addWidget(_btnUseSobelsFilter);



};

MyGUI::~MyGUI()
{
    delete _layoutMain;
};