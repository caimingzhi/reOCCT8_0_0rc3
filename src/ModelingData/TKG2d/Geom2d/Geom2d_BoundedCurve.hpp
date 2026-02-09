#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom2d_Curve.hpp>
class gp_Pnt2d;

class Geom2d_BoundedCurve : public Geom2d_Curve
{

public:
  Standard_EXPORT virtual gp_Pnt2d EndPoint() const = 0;

  Standard_EXPORT virtual gp_Pnt2d StartPoint() const = 0;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom2d_BoundedCurve, Geom2d_Curve)
};
