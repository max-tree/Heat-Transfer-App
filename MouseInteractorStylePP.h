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

#include <QDebug>

// Define interaction style
class MouseInteractorStylePP : public vtkInteractorStyleTrackballCamera
{
public:
  static MouseInteractorStylePP* New();
  vtkTypeMacro(MouseInteractorStylePP, vtkInteractorStyleTrackballCamera);

  virtual void OnLeftButtonDown() override
  {
    std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
    this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                                        this->Interactor->GetEventPosition()[1],
                                        0,  // always zero.
                                        this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
    double picked[3];
    this->Interactor->GetPicker()->GetPickPosition(picked);
    qDebug() << "Picked value: ";
             qDebug() << picked[0];
                qDebug() << " ";
                qDebug() << picked[1];
                qDebug() <<" ";
                qDebug() <<picked[2];
    // Forward events
    vtkInteractorStyleTrackballCamera::OnLeftButtonDown();


  }
};

//vtkStandardNewMacro(MouseInteractorStylePP);

#endif // MOUSEINTERACTORSTYLEPP_H
