#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <gp_Pnt2d.hpp>
#include <NCollection_Array1.hpp>
class Geom2d_Line;
class Geom2d_Curve;
class Geom2d_BSplineCurve;

//! Converts curve2d to analytical form with given
//! precision or simplify curve2d.
class ShapeCustom_Curve2d
{
public:
  DEFINE_STANDARD_ALLOC

  //! Check if poleses is in the plane with given precision
  //! Returns false if no.
  Standard_EXPORT static bool IsLinear(const NCollection_Array1<gp_Pnt2d>& thePoles,
                                       const double                        theTolerance,
                                       double&                             theDeviation);

  //! Try to convert BSpline2d or Bezier2d to line 2d
  //! only if it is linear. Recalculate first and last parameters.
  //! Returns line2d or null curve2d.
  Standard_EXPORT static occ::handle<Geom2d_Line> ConvertToLine2d(
    const occ::handle<Geom2d_Curve>& theCurve,
    const double                     theFirstIn,
    const double                     theLastIn,
    const double                     theTolerance,
    double&                          theNewFirst,
    double&                          theNewLast,
    double&                          theDeviation);

  //! Try to remove knots from bspline where local derivatives are the same.
  //! Remove knots with given precision.
  //! Returns false if Bsplien was not modified
  Standard_EXPORT static bool SimplifyBSpline2d(occ::handle<Geom2d_BSplineCurve>& theBSpline2d,
                                                const double                      theTolerance);
};
