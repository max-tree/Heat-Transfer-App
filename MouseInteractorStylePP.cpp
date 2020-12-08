#include "MouseInteractorStylePP.h"
#include <QDebug>

void MouseInteractorStylePP::calculate_nearest_node() //does not work yet because I cannot get the mouse callback to communicate with mainwindow.
{
//    qDebug() << HTWCalculated.nodeStorage.size();
//    std::vector <double> nodeDistanceFromClickedLocation;
//    double distance{0.0};

//    for(int index{0}; index < HTWCalculated.numberOfNodes;index++)
//    {
//        distance = sqrt(pow(coordinateClicked[0]-HTWCalculated.nodeStorage[index]->xCoordinate,2) + pow(coordinateClicked[1]-HTWCalculated.nodeStorage[index]->yCoordinate,2));
//        nodeDistanceFromClickedLocation.push_back(distance);
//        qDebug() << nodeDistanceFromClickedLocation.size();
//    }
//    double distancePlaceholder{nodeDistanceFromClickedLocation[0]};
//    int indexPlaceholder{0};
//    for(int index{1}; index < HTWCalculated.numberOfNodes;index++)
//    {
//        if(distancePlaceholder > nodeDistanceFromClickedLocation[index])
//        {
//            distancePlaceholder = nodeDistanceFromClickedLocation[index];
//            indexPlaceholder = index;
//        }
//    }
//    qDebug() << "Node # = ";
//    qDebug() << indexPlaceholder;
}

void MouseInteractorStylePP::OnLeftButtonDown()
{
  this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                                      this->Interactor->GetEventPosition()[1],
                                      0,
                                      this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
  this->Interactor->GetPicker()->GetPickPosition(coordinateClicked);
  debugMouseClickEvent(coordinateClicked);
  calculate_nearest_node();
  vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void MouseInteractorStylePP::debugMouseClickEvent(double coordinateClicked[3])
{
    qDebug() << "Picked value: ";
    qDebug() << coordinateClicked[0];
    qDebug() << " ";
    qDebug() << coordinateClicked[1];
    qDebug() <<" ";
    qDebug() << coordinateClicked[2];

    qDebug() << "HTWCalculated = ";
    qDebug() << HTWCalculated.get_thermal_conductivity();
}
