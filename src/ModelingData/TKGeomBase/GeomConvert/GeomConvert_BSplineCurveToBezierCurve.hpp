#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Integer.hpp>
#include <Geom_BezierCurve.hpp>
#include <NCollection_Array1.hpp>
class Geom_BSplineCurve;
class Geom_BezierCurve;

class GeomConvert_BSplineCurveToBezierCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_BSplineCurveToBezierCurve(
    const occ::handle<Geom_BSplineCurve>& BasisCurve);

  Standard_EXPORT GeomConvert_BSplineCurveToBezierCurve(
    const occ::handle<Geom_BSplineCurve>& BasisCurve,
    const double                          U1,
    const double                          U2,
    const double                          ParametricTolerance);

  Standard_EXPORT occ::handle<Geom_BezierCurve> Arc(const int Index);

  Standard_EXPORT void Arcs(NCollection_Array1<occ::handle<Geom_BezierCurve>>& Curves);

  Standard_EXPORT void Knots(NCollection_Array1<double>& TKnots) const;

  Standard_EXPORT int NbArcs() const;

private:
  occ::handle<Geom_BSplineCurve> myCurve;
};
