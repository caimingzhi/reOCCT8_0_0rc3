#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
class Geom2d_Line;
class Geom2d_Curve;
class Geom2d_BSplineCurve;

class ShapeCustom_Curve2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static bool IsLinear(const NCollection_Array1<gp_Pnt2d>& thePoles,
                                       const double                        theTolerance,
                                       double&                             theDeviation);

  Standard_EXPORT static occ::handle<Geom2d_Line> ConvertToLine2d(
    const occ::handle<Geom2d_Curve>& theCurve,
    const double                     theFirstIn,
    const double                     theLastIn,
    const double                     theTolerance,
    double&                          theNewFirst,
    double&                          theNewLast,
    double&                          theDeviation);

  Standard_EXPORT static bool SimplifyBSpline2d(occ::handle<Geom2d_BSplineCurve>& theBSpline2d,
                                                const double                      theTolerance);
};
