#pragma once

#include <IVtk_Interface.hpp>
#include <gp_XY.hpp>
#include <gp_XYZ.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Mat4.hpp>
#include <Standard_TypeDef.hpp>

class IVtk_IView : public IVtk_Interface
{

public:
  typedef occ::handle<IVtk_IView> Handle;

  ~IVtk_IView() override = default;

  virtual bool IsPerspective() const = 0;

  virtual double GetDistance() const = 0;

  virtual void GetEyePosition(double& theX, double& theY, double& theZ) const = 0;

  virtual void GetPosition(double& theX, double& theY, double& theZ) const = 0;

  virtual void GetViewUp(double& theDx, double& theDy, double& theDz) const = 0;

  virtual void GetDirectionOfProjection(double& theDx, double& theDy, double& theDz) const = 0;

  virtual void GetScale(double& theX, double& theY, double& theZ) const = 0;

  virtual double GetParallelScale() const = 0;

  virtual double GetViewAngle() const = 0;

  virtual void GetClippingRange(double& theZNear, double& theZFar) const = 0;

  virtual double GetAspectRatio() const = 0;

  virtual void GetViewCenter(double& theX, double& theY) const = 0;

  virtual void GetWindowSize(int& theX, int& theY) const = 0;

  virtual void GetCamera(NCollection_Mat4<double>& theProj,
                         NCollection_Mat4<double>& theOrient,
                         bool&                     theIsOrtho) const = 0;

  virtual bool DisplayToWorld(const gp_XY& theDisplayPnt, gp_XYZ& theWorldPnt) const = 0;

  virtual void GetViewport(double& theX,
                           double& theY,
                           double& theWidth,
                           double& theHeight) const = 0;

  DEFINE_STANDARD_RTTIEXT(IVtk_IView, IVtk_Interface)
};
