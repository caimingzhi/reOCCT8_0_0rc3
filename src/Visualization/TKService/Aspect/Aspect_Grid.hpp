#pragma once

#include <Standard.hpp>

#include <Quantity_Color.hpp>
#include <Aspect_GridDrawMode.hpp>
#include <Standard_Transient.hpp>

class Aspect_Grid : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Aspect_Grid, Standard_Transient)
public:
  Standard_EXPORT void SetXOrigin(const double anOrigin);

  Standard_EXPORT void SetYOrigin(const double anOrigin);

  Standard_EXPORT void SetRotationAngle(const double anAngle);

  Standard_EXPORT void Rotate(const double anAngle);

  Standard_EXPORT void Translate(const double aDx, const double aDy);

  Standard_EXPORT virtual void SetColors(const Quantity_Color& aColor,
                                         const Quantity_Color& aTenthColor);

  Standard_EXPORT void Hit(const double X, const double Y, double& gridX, double& gridY) const;

  Standard_EXPORT virtual void Compute(const double X,
                                       const double Y,
                                       double&      gridX,
                                       double&      gridY) const = 0;

  void Activate() { myIsActive = true; }

  void Deactivate() { myIsActive = false; }

  double XOrigin() const { return myXOrigin; }

  double YOrigin() const { return myYOrigin; }

  double RotationAngle() const { return myRotationAngle; }

  bool IsActive() const { return myIsActive; }

  Standard_EXPORT void Colors(Quantity_Color& aColor, Quantity_Color& aTenthColor) const;

  Standard_EXPORT void SetDrawMode(const Aspect_GridDrawMode aDrawMode);

  Aspect_GridDrawMode DrawMode() const { return myDrawMode; }

  Standard_EXPORT virtual void Display() = 0;

  Standard_EXPORT virtual void Erase() const = 0;

  Standard_EXPORT virtual bool IsDisplayed() const = 0;

  Standard_EXPORT virtual void Init() = 0;

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT Aspect_Grid(const double          theXOrigin       = 0.0,
                              const double          theYOrigin       = 0.0,
                              const double          theRotationAngle = 0,
                              const Quantity_Color& theColor         = Quantity_NOC_GRAY50,
                              const Quantity_Color& theTenthColor    = Quantity_NOC_GRAY70);

  Standard_EXPORT virtual void UpdateDisplay() = 0;

protected:
  double              myRotationAngle;
  double              myXOrigin;
  double              myYOrigin;
  Quantity_Color      myColor;
  Quantity_Color      myTenthColor;
  bool                myIsActive;
  Aspect_GridDrawMode myDrawMode;
};
