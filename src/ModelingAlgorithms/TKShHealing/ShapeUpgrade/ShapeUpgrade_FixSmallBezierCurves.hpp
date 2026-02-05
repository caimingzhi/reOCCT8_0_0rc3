#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <ShapeUpgrade_FixSmallCurves.hpp>
class Geom_Curve;
class Geom2d_Curve;

class ShapeUpgrade_FixSmallBezierCurves : public ShapeUpgrade_FixSmallCurves
{

public:
  Standard_EXPORT ShapeUpgrade_FixSmallBezierCurves();

  Standard_EXPORT bool Approx(occ::handle<Geom_Curve>&   Curve3d,
                              occ::handle<Geom2d_Curve>& Curve2d,
                              occ::handle<Geom2d_Curve>& Curve2dR,
                              double&                    First,
                              double&                    Last) override;

  DEFINE_STANDARD_RTTIEXT(ShapeUpgrade_FixSmallBezierCurves, ShapeUpgrade_FixSmallCurves)
};
