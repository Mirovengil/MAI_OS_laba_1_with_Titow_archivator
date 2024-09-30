#include <iostream>
#include "ImageMatrix.h"
#include "TCore.h"
#include "GUI.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MyGUI gui;
    gui.show();
    return app.exec();
}