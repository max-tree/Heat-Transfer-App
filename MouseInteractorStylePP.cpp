#include "MouseInteractorStylePP.h"
#include <QDebug>

void debugMouseClickEvent(double picked[3]);

void MouseInteractorStylePP::OnLeftButtonDown()
{
  this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                                      this->Interactor->GetEventPosition()[1],
                                      0,  // always zero.
                                      this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
  double picked[3]{0.0,0.0,0.0};
  this->Interactor->GetPicker()->GetPickPosition(picked);
  debugMouseClickEvent(picked);

  vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
}

void debugMouseClickEvent(double picked[3])
{
    qDebug() << "Picked value: ";
    qDebug() << picked[0];
    qDebug() << " ";
    qDebug() << picked[1];
    qDebug() <<" ";
    qDebug() <<picked[2];
}
