#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <GeomToStep_Root.hpp>

class StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve;
class Geom_BSplineCurve;
class Geom2d_BSplineCurve;

//! This class implements the mapping between classes
//! BSplineCurve from Geom, Geom2d and the class
//! BSplineCurveWithKnotsAndRationalBSplineCurve from StepGeom
//! which describes a rational_bspline_curve_with_knots from
//! Prostep
class GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve : public GeomToStep_Root
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve(
    const occ::handle<Geom_BSplineCurve>& Bsplin,
    const StepData_Factors&               theLocalFactors = StepData_Factors());

  Standard_EXPORT GeomToStep_MakeBSplineCurveWithKnotsAndRationalBSplineCurve(
    const occ::handle<Geom2d_BSplineCurve>& Bsplin,
    const StepData_Factors&                 theLocalFactors = StepData_Factors());

  Standard_EXPORT const occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve>& Value()
    const;

private:
  occ::handle<StepGeom_BSplineCurveWithKnotsAndRationalBSplineCurve>
    theBSplineCurveWithKnotsAndRationalBSplineCurve;
};

