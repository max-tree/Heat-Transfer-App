//-------------------------------------------------------
// Filename: main.cpp
//
// Description:  Finite Difference Heat Transfer Application.
//
// Creation Date: 12/8/2020
//
// Owner: Maxwell Tree
// Built off of an example by: Corey McBride and others.
//-------------------------------------------------------
#include <QApplication>
#include "mainwindow.h"
#include <QVTKOpenGlWidget.h>

int main(int argc, char *argv[])
{
    QSurfaceFormat::setDefaultFormat(QVTKOpenGLWidget::defaultFormat());

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
