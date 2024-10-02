#include "GUI.h"
#include <QStringList>
#include <QSize>
#include "Matrix.h"
#include <math.h>

const QSize _stdSizeOfGUIWindow = {1200, 800}; 
const QSize _stdSizeOfImageLabel = {1200, 600};
const int _stdValueOfSlider = 0;
const int _maxValueOfSlider = 7;
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
    _sliderNumberOfThreads->setMinimum(0);                  // 2^0 = 1 поток
    _sliderNumberOfThreads->setMaximum(_maxValueOfSlider);  // 2^7 = 128 потоков
    _sliderNumberOfThreads->setValue(_stdValueOfSlider);
    _layoutMain->addWidget(_sliderNumberOfThreads);

    _threads.resize((1<<_maxValueOfSlider));
    for (int i = 0; i < _threads.size(); ++i)
        _threads[i] = new MyThread;

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

    _timerOfProcessing = new QElapsedTimer;
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
    ImageMatrix resultImageMatrix(_imageMatrix->getN(), _imageMatrix->getM());
    QImage resultImage(_imageMatrix->getN(), _imageMatrix->getM(), QImage::Format_RGB32);

    qint64 processingTimeElapsed;

    // здесь начинается многопоточка и замер времени
    for (int i = 0; i < _numberOfThreads; ++i)
    {
        int from, to;

        from = (_imageMatrix->getN() / _numberOfThreads) * i;
        to = std::min((_imageMatrix->getN() / _numberOfThreads) * (i+1), _imageMatrix->getN());
        if (i + 1 == _numberOfThreads)
            to = _imageMatrix->getN();
        

        _threads[i]->setOrigMatrix(_imageMatrix);
        _threads[i]->setMatrixOfLuminocity(&matrixOfLuminosity);
        _threads[i]->setMatrixOfXYConvolution(&matrixOfXConvolution, &matrixOfYConvolution);
        _threads[i]->setResultImageMatrix(&resultImageMatrix);
        _threads[i]->setResultImage(&resultImage);
        _threads[i]->setFunctorOfLuminocity(luminosityFunctor);
        _threads[i]->setFunctorOfPow2(pow2Functor);
        _threads[i]->setFunctorOfSqrt(sqrtFunctor);
        _threads[i]->setLines(from, to);
        _threads[i]->setBordersProcessing((i==0), (i+1==_numberOfThreads));

    }

    _timerOfProcessing->start();
    for (int i = 0; i < _numberOfThreads; ++i)
        _threads[i]->start();    


    for (int i = 0; i < _numberOfThreads; ++i)
        _threads[i]->wait();
    processingTimeElapsed = _timerOfProcessing->elapsed();
    
    for (int i = 0; i < _numberOfThreads; ++i)
        _threads[i]->reset();

    QPixmap temporalPixmap = QPixmap::fromImage(resultImage);
    _lblImagePreview->setPixmap(temporalPixmap.scaled(_stdSizeOfImageLabel, Qt::KeepAspectRatio));

    _messageBoxTimesResult->setText("Потрачено на обработку изображения: " + 
        QString::number(processingTimeElapsed) + "мс");
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
    for (int i = 0; i < _threads.size(); ++i)
        delete _threads[i];
    delete _timerOfProcessing;
};