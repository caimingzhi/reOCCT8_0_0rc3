#pragma once

#include <V3d_View.hpp>

class V3d_Plane : public Standard_Transient
{
public:
  Standard_EXPORT V3d_Plane(const double theA = 0.0,
                            const double theB = 0.0,
                            const double theC = 1.0,
                            const double theD = 0.0);

  Standard_EXPORT void SetPlane(const double theA,
                                const double theB,
                                const double theC,
                                const double theD);

  Standard_EXPORT virtual void Display(const occ::handle<V3d_View>& theView,
                                       const Quantity_Color&        theColor = Quantity_NOC_GRAY);

  Standard_EXPORT void Erase();

  Standard_EXPORT void Plane(double& theA, double& theB, double& theC, double& theD) const;

  Standard_EXPORT bool IsDisplayed() const;

  const occ::handle<Graphic3d_ClipPlane>& ClipPlane() const { return myPlane; }

private:
  Standard_EXPORT void Update();

protected:
  occ::handle<Graphic3d_Structure> myGraphicStructure;

private:
  occ::handle<Graphic3d_ClipPlane> myPlane;

public:
  DEFINE_STANDARD_RTTIEXT(V3d_Plane, Standard_Transient)
};
