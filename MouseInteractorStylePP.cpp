#include "MouseInteractorStylePP.h"
#include <QString>

void display_nearest_node(int nearestNode)
{
    QMessageBox msgBox;
    QString node = QString::number(nearestNode);

    msgBox.setText(node);
    msgBox.setWindowTitle("The closest node is");

    msgBox.isActiveWindow();
    msgBox.exec();
}

int MouseInteractorStylePP::calculate_nearest_node()
{
    std::vector <double> nodeDistanceFromClick;
    int numberOfNodes = nodeXCoodrinateStorage.size();
    double distance{0.0};

    for(int index{0}; index < numberOfNodes;index++)
    {
        distance = sqrt(pow(coordinateClicked[0]-nodeXCoodrinateStorage[index],2) +
                pow(coordinateClicked[1]-nodeYCoordinateStorage[index],2));
        nodeDistanceFromClick.push_back(distance);
    }

    double distancePlaceholder{nodeDistanceFromClick[0]};
    int nearestNode{0};

    for(int index{1}; index < numberOfNodes;index++)
    {
        if(distancePlaceholder > nodeDistanceFromClick[index])
        {
            distancePlaceholder = nodeDistanceFromClick[index];
            nearestNode = index;
        }
    }
    return nearestNode;
}

void MouseInteractorStylePP::OnLeftButtonDown()
{
  this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                                      this->Interactor->GetEventPosition()[1],
                                      0,
                                      this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
  this->Interactor->GetPicker()->GetPickPosition(coordinateClicked);
  display_nearest_node(calculate_nearest_node());
}
