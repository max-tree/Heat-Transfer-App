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

#include <vtkExodusIIReader.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkPolyDataMapper.h>

#include <vtkCamera.h>
#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleUser.h>
#include <vtkProperty.h>
#include <vtkCommand.h>
#include <vtkPointData.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkDoubleArray.h>
#include <vtkDataSetMapper.h>
#include <vtkClipDataSet.h>
#include <vtkPlane.h>
#include <vtkUnstructuredGrid.h>
#include <vtkScalarBarActor.h>
#include <vtkLookupTable.h>
#include <QFileDialog>
#include <vtkGenericOpenGLRenderWindow.h>
#include <QVector3D>
#include <QVTKOpenGLWidget.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkCompositeDataIterator.h>

#include "HeatTransferWorld.h"
#include "HeatTransferNode.h"

#include "MouseInteractorStylePP.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    HeatTransferWorld HTW;
    vtkSmartPointer<MouseInteractorStylePP> style =
            vtkSmartPointer<MouseInteractorStylePP>::New();
    void add_window_to_rendering();
    void create_actor(vtkPolyDataMapper* actor);
    void create_geometry(vtkExodusIIReader* reader);
    void create_mapper(vtkCompositeDataGeometryFilter* reader);
    void create_layout();
    void iterate(vtkExodusIIReader* reader);
    QString read_in_filename();
    void render_this_instance();
    void set_background_render(std::array <double,3> color);
    void fill_data_array(vtkUnstructuredGrid* unstructuredGrid, vtkDoubleArray* data);
    void create_mouse_interactor();
    void transfer_heat_transfer_data_to_mouse_event_class(); //Failed attempt at transferring the data from mainwindow to the PointPicker class...

protected slots:
    void setup();

private:
    Ui::MainWindow *ui;
    QVTKOpenGLWidget* mQVtkWidget;
    std::array <double,3> lightGrey{0.8,0.8,0.8};
    vtkNew<vtkRenderer> mRenderer;
};

void configure_reader(vtkExodusIIReader* reader, QString filename);
void set_the_new_data_on_the_mesh(vtkUnstructuredGrid* unstructuredGrid, vtkDoubleArray* data);
double calculate_distance_from_the_origin(double pt[3]);

#endif // MAINWINDOW_H
