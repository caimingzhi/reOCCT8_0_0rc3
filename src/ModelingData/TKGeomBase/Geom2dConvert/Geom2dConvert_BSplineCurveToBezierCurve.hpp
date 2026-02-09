#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <NCollection_Array1.hpp>
class Geom2d_BSplineCurve;
class Geom2d_BezierCurve;

class Geom2dConvert_BSplineCurveToBezierCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dConvert_BSplineCurveToBezierCurve(
    const occ::handle<Geom2d_BSplineCurve>& BasisCurve);

  Standard_EXPORT Geom2dConvert_BSplineCurveToBezierCurve(
    const occ::handle<Geom2d_BSplineCurve>& BasisCurve,
    const double                            U1,
    const double                            U2,
    const double                            ParametricTolerance);

  Standard_EXPORT occ::handle<Geom2d_BezierCurve> Arc(const int Index);

  Standard_EXPORT void Arcs(NCollection_Array1<occ::handle<Geom2d_BezierCurve>>& Curves);

  Standard_EXPORT void Knots(NCollection_Array1<double>& TKnots) const;

  Standard_EXPORT int NbArcs() const;

private:
  occ::handle<Geom2d_BSplineCurve> myCurve;
};
