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
#include <QDebug>

vtkStandardNewMacro(MouseInteractorStylePP);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mQVtkWidget= new QVTKOpenGLWidget(this);
    create_layout();
    add_window_to_rendering();
    setup();
    set_background_render(lightGrey);

}


MainWindow::~MainWindow()
{
    delete ui;
    delete mQVtkWidget;
}

void MainWindow::setup()
{
    QString filename = read_in_filename();

    if(filename.isEmpty())
        return;

    vtkNew<vtkExodusIIReader> reader;
    configure_reader(reader, filename);
    iterate(reader);
    create_geometry(reader);
    create_mouse_interactor();
//    render_this_instance();
}

void MainWindow::add_window_to_rendering()
{
    vtkNew<vtkGenericOpenGLRenderWindow> window;
    mQVtkWidget->SetRenderWindow(window);
    window->AddRenderer(mRenderer);
}

void MainWindow::create_actor(vtkPolyDataMapper* mapper)
{
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(0.0,1.0,0.0);

    mRenderer->AddActor(actor);
    mRenderer->ResetCamera();
}

void MainWindow::create_geometry(vtkExodusIIReader* reader)
{
    vtkNew<vtkCompositeDataGeometryFilter> geometry;
    geometry->SetInputConnection(reader->GetOutputPort());
    create_mapper(geometry);

}

void MainWindow::create_layout()
{
    QGridLayout* layout = new QGridLayout(ui->frame);
    layout->addWidget(mQVtkWidget,1,1);
    ui->frame->setLayout(layout);
}

void MainWindow::create_mapper(vtkCompositeDataGeometryFilter* geometry)
{
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(geometry->GetOutputPort());
    mapper->SetColorModeToMapScalars();
    mapper->SetScalarVisibility(1);
    create_actor(mapper);
}

void MainWindow::iterate(vtkExodusIIReader* reader)
{
    vtkSmartPointer<vtkCompositeDataSet> input = reader->GetOutput();
    vtkCompositeDataIterator* iter = input->NewIterator();
    for (iter->InitTraversal(); !iter->IsDoneWithTraversal(); iter->GoToNextItem())
      {
        vtkUnstructuredGrid* unstructuredGrid = vtkUnstructuredGrid::SafeDownCast(iter->GetCurrentDataObject());
        if(unstructuredGrid)
        {
            vtkNew<vtkDoubleArray> data;
            data->SetName("CustomData");

            vtkNew<vtkPointData> pointData;
            set_the_new_data_on_the_mesh(unstructuredGrid, data);
            //Specify that the scalar we want to color by is our custom data.
            unstructuredGrid->GetPointData()->SetActiveScalars("CustomData");
            fill_data_array(unstructuredGrid, data);
        }
    }
    iter->Delete();
}

QString MainWindow::read_in_filename()
{
   QString filename = QFileDialog::getOpenFileName(this,"Open Mesh File","","*.e;;*.exo");
   return filename;
}

void MainWindow::create_mouse_interactor()
{
    vtkSmartPointer<vtkPointPicker> pointPicker =
            vtkSmartPointer<vtkPointPicker>::New();

    vtkSmartPointer<vtkRenderWindow> renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(mRenderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetPicker(pointPicker);
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindowInteractor->SetInteractorStyle( style );
    transfer_heat_transfer_data_to_mouse_event_class();

    renderWindowInteractor->Start();
}

void MainWindow::render_this_instance()
{
    this->mQVtkWidget->GetRenderWindow()->Render();
}

void MainWindow::set_background_render(std::array <double,3> color)
{
    mRenderer->SetBackground(color[0],color[1],color[2]);
}

double calculate_distance_from_the_origin(double pt[3])
{
    QVector3D vec(pt[0],pt[1],pt[2]);
    double length = vec.length();
    return length;//Color is controled by the length from the origin. May need to create a new "setLookupTable()"
}

void configure_reader(vtkExodusIIReader* reader, QString filename)
{
    reader->SetFileName(filename.toStdString().c_str());
    reader->UpdateInformation();
    reader->SetTimeStep(0);
    reader->SetAllArrayStatus(vtkExodusIIReader::NODAL, 1);
    reader->Update();
}

void MainWindow::fill_data_array(vtkUnstructuredGrid* unstructuredGrid, vtkDoubleArray* data)
{
    vtkSmartPointer<vtkPoints> points=unstructuredGrid->GetPoints();
    vtkIdType numberOfPoints= points->GetNumberOfPoints();

    double length{0.0};

    for(vtkIdType index=0;index<numberOfPoints;index++)
    {
        double pt[3];
        HeatTransferNode* newNode = new HeatTransferNode;
        newNode->nodeIdNum = index;
        points->GetPoint(index,pt);

        set_x_and_y_coordinates(newNode, pt[0], pt[1]);

        HTW.nodeXCoordinates.push_back(pt[0]);
        HTW.nodeYCoordinates.push_back(pt[1]);

        length = calculate_distance_from_the_origin(pt);
        data->InsertNextValue(length); //0 is red, 1 is blue, 0.5 is green.

        HTW.nodeStorage.push_back(newNode);
    }
    HTW.set_deltaX_and_deltaY(calculate_distance_between_two_nodes(HTW.nodeStorage[0],HTW.nodeStorage[1]));

    for(vtkIdType index=0;index<numberOfPoints;index++)
    {
        delete HTW.nodeStorage[index];
    }
}

void set_the_new_data_on_the_mesh(vtkUnstructuredGrid* unstructuredGrid, vtkDoubleArray* data)
{
    unstructuredGrid->GetPointData()->SetScalars(data);
}

void MainWindow::transfer_heat_transfer_data_to_mouse_event_class()
{
    style->nodeXStorage = HTW.nodeXCoordinates;
    style->nodeYStorage = HTW.nodeYCoordinates;

}
