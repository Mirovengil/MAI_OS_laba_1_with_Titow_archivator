#include "GUI.h"
#include <QStringList>
#include <QDebug>   // TODO : убей меня
#include <QSize>
#include "Matrix.h"
#include <math.h>

const QSize _stdSizeOfGUIWindow = {1200, 800}; 
const QSize _stdSizeOfImageLabel = {1200, 600};
const int _stdValueOfSlider = 0;
const QString _sliderText = "Заданное число потоков: ";

MyGUI::MyGUI()
{
    this->resize(_stdSizeOfGUIWindow);

    _pixmapImageLoader = new QPixmap;

    _layoutMain = new QVBoxLayout(this);
    
    _btnSelectImage = new QPushButton;
    _btnSelectImage->setText("Выбрать изображение для обработки");
    _layoutMain->addWidget(_btnSelectImage);
    
    _lblImagePreview = new QLabel("Здесь будет изображение");
    _pixmapImageLoader->load("../pic/picture_404.png");
    _lblImagePreview->setPixmap(_pixmapImageLoader->scaled(_stdSizeOfImageLabel, Qt::KeepAspectRatio));
    
    _lblImagePreview->resize(_stdSizeOfImageLabel);
    _layoutMain->addWidget(_lblImagePreview);

    _numberOfThreads = 1;
    _lblNumberOfThreads = new QLabel(_sliderText + "1");
    _layoutMain->addWidget(_lblNumberOfThreads);
    
    _sliderNumberOfThreads = new QSlider(Qt::Horizontal);
    _sliderNumberOfThreads->setMinimum(0);  // 2^0 = 1 поток
    _sliderNumberOfThreads->setMaximum(8);  // 2^8 = 256 потоков
    _sliderNumberOfThreads->setValue(_stdValueOfSlider);
    _layoutMain->addWidget(_sliderNumberOfThreads);

    _btnUseSobelsFilter = new QPushButton;
    _btnUseSobelsFilter->setText("Применить фильтр Собела");
    _layoutMain->addWidget(_btnUseSobelsFilter);

    _btnReset = new QPushButton;
    _btnReset->setText("Сбросить результат фильтрации");
    _layoutMain->addWidget(_btnReset);

    // эти товарищи не являются детьми основного виджета, и в деструкторе их надо убивать по отдельности
    _messageBoxTimesResult = new QMessageBox;

    _fileDialogForSelectImageFile = new QFileDialog;
    _fileDialogForSelectImageFile->setNameFilter(tr("Images (*.png *.png)"));
    _fileDialogForSelectImageFile->setFileMode(QFileDialog::ExistingFile);

    _imageForProcessing = new QImage;

    // привязываю сигналы к слотам
    connect(_sliderNumberOfThreads, &QSlider::valueChanged, this, &MyGUI::renewNumberOfThreads);
    connect(_btnUseSobelsFilter, &QPushButton::pressed, this, &MyGUI::makeProcessing);
    connect(_btnSelectImage, &QPushButton::pressed, this, &MyGUI::selectImageFile);
    connect(_btnReset, &QPushButton::pressed, this, &MyGUI::resetImageToNonFiltered);

    // здесь -- стартовые значения обработки
    _imageMatrix = nullptr;
};

void MyGUI::resetImageToNonFiltered()
{
    _lblImagePreview->setPixmap(_pixmapImageLoader->scaled(_stdSizeOfImageLabel, Qt::KeepAspectRatio));
};

void MyGUI::selectImageFile()
{
    QStringList selectedFile;
    if (_fileDialogForSelectImageFile->exec())
    {
        selectedFile = _fileDialogForSelectImageFile->selectedFiles();
        _openImage(selectedFile[0]);
        if (_imageMatrix != nullptr)
        {
            delete _imageMatrix;
            _imageMatrix = nullptr;
        }
    }
};

void MyGUI::_openImage(QString filename)
{
    _pixmapImageLoader->load(filename);
    _lblImagePreview->setPixmap(_pixmapImageLoader->scaled(_stdSizeOfImageLabel, Qt::KeepAspectRatio));
};  

void MyGUI::makeProcessing()
{
    *_imageForProcessing = _pixmapImageLoader->toImage();

    // вот это я не добавляю в многопоточку, потому что иначе замеры для случаев, когда картинка уже считана
    // и когда -- ещё нет, будут сильно разниться. 
    if (_imageMatrix == nullptr)
        _imageMatrix = new ImageMatrix(_imageForProcessing);

    auto luminosityFunctor =  [](RGBCell rgbCell)
        {
            return (int)rgbCell.getLuminosity();
        };
    auto pow2Functor = [](int value)
        {
            return value * value;
        };
    auto sqrtFunctor = [](int value)
    {
        double result = sqrt(value);
        result = result * 255.0 / 1442.5;
        return (int)result;
    };

    // выделяю сразу всю память перед тем, как начать замер времени
    Matrix matrixOfLuminosity(_imageMatrix->getN(), _imageMatrix->getM());
    Matrix matrixOfXConvolution(_imageMatrix->getN(), _imageMatrix->getM());
    Matrix matrixOfYConvolution(_imageMatrix->getN(), _imageMatrix->getM());
    ImageMatrix resultImage(_imageMatrix->getN(), _imageMatrix->getM());
    QImage operatedImage;

    // здесь начинается многопоточка и замер времени

    // TODO : добавить многопоточку
    matrixOfLuminosity.fillWithImageMatrix(*_imageMatrix, luminosityFunctor, 0, _imageMatrix->getN());

    // TODO : добавить многопоточку
    matrixOfLuminosity.doConvolution(SobelsMatrixX, matrixOfXConvolution, 1, _imageMatrix->getN()-1);
    matrixOfLuminosity.doConvolution(SobelsMatrixY, matrixOfYConvolution, 1, _imageMatrix->getN()-1);


    // TODO : добавить многопоточку
    matrixOfXConvolution.useFunctionToCells(pow2Functor, 1, _imageMatrix->getN()-1);
    matrixOfYConvolution.useFunctionToCells(pow2Functor, 1, _imageMatrix->getN()-1);

    // чтоб не порождать новые, занимающие дофига памяти, сущности
    matrixOfXConvolution.summWith(matrixOfYConvolution, 1, _imageMatrix->getN()-1);

    // TODO : добавить многопоточку
    matrixOfXConvolution.useFunctionToCells(sqrtFunctor, 1, _imageMatrix->getN() - 1);
    
    resultImage = matrixOfXConvolution.convertToImageMatrix();


    operatedImage = resultImage.convertToImage();
    
    // здесь уже можно заканчивать замер времени
    
    QPixmap temporalPixmap = QPixmap::fromImage(operatedImage);
    _lblImagePreview->setPixmap(temporalPixmap.scaled(_stdSizeOfImageLabel, Qt::KeepAspectRatio));

    _messageBoxTimesResult->setText("А вот тут будет временной замер: ABOBA!!!\n");
    _messageBoxTimesResult->exec();
};

void MyGUI::renewNumberOfThreads()
{
    _numberOfThreads = 1 << _sliderNumberOfThreads->value();
    _lblNumberOfThreads->setText(_sliderText + QString::number(_numberOfThreads));
};

MyGUI::~MyGUI()
{
    delete _layoutMain;
    delete _messageBoxTimesResult;
    delete _fileDialogForSelectImageFile;
    delete _imageForProcessing;
    delete _imageMatrix;
};