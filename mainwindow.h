//-------------------------------------------------------
// Filename: mainwindow.cpp
//
// Description:  The cpp file for the qt5 bullet bouncy ball example.
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 11/8/2018
//
// Owner: Corey McBride
//-------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QVTKOpenGLWidget.h>
#include <vtkSmartPointer.h>
#include <vtkPlane.h>
#include <array>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void create_layout();
    void add_window_to_rendering();
    void set_background_render(std::array <double,3> color);


protected slots:
    void setup();

private:
    Ui::MainWindow *ui;
    QVTKOpenGLWidget* mQVtkWidget;
    std::array <double,3> lightGrey{0.8,0.8,0.8};
    vtkNew<vtkRenderer> mRenderer;
};

#endif // MAINWINDOW_H
