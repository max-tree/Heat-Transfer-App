#ifndef MOUSEINTERACTORSTYLEPP_H
#define MOUSEINTERACTORSTYLEPP_H

#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkPointPicker.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>

#include "HeatTransferWorld.h"
#include "HeatTransferNode.h"

#include <vector>
#include "math.h"
#include <QMessageBox>

class MouseInteractorStylePP : public vtkInteractorStyleTrackballCamera
{
public:
    static MouseInteractorStylePP* New();

    vtkTypeMacro(MouseInteractorStylePP, vtkInteractorStyleTrackballCamera);

    virtual void OnLeftButtonDown() override;
    int calculate_nearest_node();

    double coordinateClicked[3]{0.0,0.0,0.0};
    std::vector <double> nodeXCoodrinateStorage;
    std::vector <double> nodeYCoordinateStorage;
};

void display_nearest_node(int nearestNode);

#endif // MOUSEINTERACTORSTYLEPP_H
