#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Geom_Curve.hpp>
class gp_Pnt;

class Geom_BoundedCurve : public Geom_Curve
{

public:
  Standard_EXPORT virtual gp_Pnt EndPoint() const = 0;

  Standard_EXPORT virtual gp_Pnt StartPoint() const = 0;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_STANDARD_RTTIEXT(Geom_BoundedCurve, Geom_Curve)
};
