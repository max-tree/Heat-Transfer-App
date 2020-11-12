//-------------------------------------------------------
// Filename: mainwindow.cpp
//
// Description:  The cpp file for the VTK Exodus Reader Example.
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 11/12/2020
//
// Owner: Corey McBride
//-------------------------------------------------------
#include "mainwindow.h"
#include "ui_mainwindow.h"
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
#include <vtkExodusIIReader.h>
#include <vtkCompositeDataGeometryFilter.h>
#include <vtkMultiBlockDataSet.h>
#include <vtkPolyDataMapper.h>
#include <vtkCompositeDataIterator.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mQVtkWidget= new QVTKOpenGLWidget(this);

    QGridLayout* layout = new QGridLayout(ui->frame);
    layout->addWidget(mQVtkWidget,1,1);
    ui->frame->setLayout(layout);

    vtkNew<vtkGenericOpenGLRenderWindow> window;
    mQVtkWidget->SetRenderWindow(window);

    window->AddRenderer(mRenderer);
    setup();
    mRenderer->GradientBackgroundOn();
    mRenderer->SetBackground(1,1,1);
    mRenderer->SetBackground2(0,0,0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup()
{
    //Open mesh file.
    QString filename=QFileDialog::getOpenFileName(this,"Open Mesh File","","*.e;;*.exo");

    if(filename.isEmpty())
        return;
    vtkNew<vtkExodusIIReader> reader;
    reader->SetFileName(filename.toStdString().c_str());
    reader->UpdateInformation();
    reader->SetTimeStep(0);
    reader->SetAllArrayStatus(vtkExodusIIReader::NODAL, 1);


    reader->Update();
    vtkSmartPointer<vtkCompositeDataSet> input= reader->GetOutput();

    vtkCompositeDataIterator* iter = input->NewIterator();
    for (iter->InitTraversal(); !iter->IsDoneWithTraversal(); iter->GoToNextItem())
      {
        vtkUnstructuredGrid* unstructuredGrid = vtkUnstructuredGrid::SafeDownCast(iter->GetCurrentDataObject());

        if(unstructuredGrid)
        {
            //Create a new data array
            vtkNew<vtkDoubleArray> data;
            data->SetName("CustomData");

            vtkNew<vtkPointData> pointData;
            // unstructuredGrid->
            //Set the new data on the mesh
            unstructuredGrid->GetPointData()->SetScalars(data);
            //Specify that the scalar we want to color by is our custom data.
            unstructuredGrid->GetPointData()->SetActiveScalars("CustomData");


            //Fill in the data with values of interest.
            //One value for each point.
            vtkSmartPointer<vtkPoints> points=unstructuredGrid->GetPoints();
            vtkIdType number_points= points->GetNumberOfPoints();
            for(vtkIdType i=0;i<number_points;i++)
            {
                double pt[3];
                points->GetPoint(i,pt);

                //Calculate the custom data.
                //For this example we are using the distance from the origin.
                //Calculate the distance from origin.
                QVector3D vec(pt[0],pt[1],pt[2]);
                double length = vec.length();

                //Insert the custom data into the data array.
                data->InsertNextValue(length);
            }
        }
    }
    iter->Delete();

    // Create Geometry
    vtkNew<vtkCompositeDataGeometryFilter> geometry;
    geometry->SetInputConnection(reader->GetOutputPort());

    // Mapper
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(geometry->GetOutputPort());
    mapper->SetColorModeToDefault();
    mapper->SetScalarVisibility(1);

    // Actor
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    mRenderer->AddActor(actor);
    mRenderer->ResetCamera();

    this->mQVtkWidget->GetRenderWindow()->Render();
}
