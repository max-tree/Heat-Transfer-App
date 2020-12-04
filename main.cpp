//-------------------------------------------------------
// Filename: main.cpp
//
// Description:  The cpp file for the qt5 bullet bouncy ball example.
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 11/8/2018
//
// Owner: Corey McBride
//-------------------------------------------------------
#include <QApplication>
#include "mainwindow.h"
#include <QVTKOpenGlWidget.h>
//Consider using QDebug to be able to debug stuff like normal.

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
