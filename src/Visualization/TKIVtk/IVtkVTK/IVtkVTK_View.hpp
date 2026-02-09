#pragma once

#include <IVtk_IView.hpp>
#include <vtkSmartPointer.h>

class vtkRenderer;

class IVtkVTK_View : public IVtk_IView
{

public:
  typedef occ::handle<IVtkVTK_View> Handle;

  Standard_EXPORT IVtkVTK_View(vtkRenderer* theRenderer);

  Standard_EXPORT ~IVtkVTK_View() override;

  Standard_EXPORT bool IsPerspective() const override;

  Standard_EXPORT double GetDistance() const override;

  Standard_EXPORT void GetEyePosition(double& theX, double& theY, double& theZ) const override;

  Standard_EXPORT void GetPosition(double& theX, double& theY, double& theZ) const override;

  Standard_EXPORT void GetViewUp(double& theDx, double& theDy, double& theDz) const override;

  Standard_EXPORT void GetDirectionOfProjection(double& theDx,
                                                double& theDy,
                                                double& theDz) const override;

  Standard_EXPORT void GetScale(double& theX, double& theY, double& theZ) const override;

  Standard_EXPORT double GetParallelScale() const override;

  Standard_EXPORT double GetViewAngle() const override;

  Standard_EXPORT void GetClippingRange(double& theZNear, double& theZFar) const override;

  Standard_EXPORT double GetAspectRatio() const override;

  Standard_EXPORT void GetViewCenter(double& theX, double& theY) const override;

  Standard_EXPORT void GetWindowSize(int& theX, int& theY) const override;

  Standard_EXPORT void GetCamera(NCollection_Mat4<double>& theProj,
                                 NCollection_Mat4<double>& theOrient,
                                 bool&                     theIsOrtho) const override;

  Standard_EXPORT void GetViewport(double& theX,
                                   double& theY,
                                   double& theWidth,
                                   double& theHeight) const override;

  Standard_EXPORT bool DisplayToWorld(const gp_XY& theDisplayPnt,
                                      gp_XYZ&      theWorldPnt) const override;

  DEFINE_STANDARD_RTTIEXT(IVtkVTK_View, IVtk_IView)

private:
  vtkSmartPointer<vtkRenderer> myRenderer;
};
