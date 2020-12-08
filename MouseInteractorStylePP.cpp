#include "MouseInteractorStylePP.h"
#include <QDebug>

void MouseInteractorStylePP::calculate_nearest_node()
{

    std::vector <double> nodeDistanceFromClick;
    int numberOfNodes = nodeXCoodrinateStorage.size();
    double distance{0.0};

    for(int index{0}; index < numberOfNodes;index++)
    {
        distance = sqrt(pow(coordinateClicked[0]-nodeXCoodrinateStorage[index],2) + pow(coordinateClicked[1]-nodeYCoordinateStorage[index],2));
        nodeDistanceFromClick.push_back(distance);
    }
    double distancePlaceholder{nodeDistanceFromClick[0]};
    int indexPlaceholder{0};
    for(int index{1}; index < numberOfNodes;index++)
    {
        if(distancePlaceholder > nodeDistanceFromClick[index])
        {
            distancePlaceholder = nodeDistanceFromClick[index];
            indexPlaceholder = index;
        }
        qDebug() << "Node # = ";
        qDebug() << indexPlaceholder;
    }
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
}
