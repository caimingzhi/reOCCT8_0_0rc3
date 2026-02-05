#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom_Curve;

//! Converts BSpline curve to periodic
class ShapeCustom_Curve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT ShapeCustom_Curve();

  Standard_EXPORT ShapeCustom_Curve(const occ::handle<Geom_Curve>& C);

  Standard_EXPORT void Init(const occ::handle<Geom_Curve>& C);

  //! Tries to convert the Curve to the Periodic form
  //! Returns the resulting curve
  //! Works only if the Curve is BSpline and is closed with
  //! Precision::Confusion()
  //! Else, or in case of failure, returns a Null Handle
  Standard_EXPORT occ::handle<Geom_Curve> ConvertToPeriodic(const bool   substitute,
                                                            const double preci = -1);

private:
  occ::handle<Geom_Curve> myCurve;
};
