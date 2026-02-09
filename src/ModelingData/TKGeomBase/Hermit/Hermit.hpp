#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_BSplineCurve;
class Geom_BSplineCurve;

class Hermit
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT static occ::handle<Geom2d_BSplineCurve> Solution(
    const occ::handle<Geom_BSplineCurve>& BS,
    const double                          TolPoles = 0.000001,
    const double                          TolKnots = 0.000001);

  Standard_EXPORT static occ::handle<Geom2d_BSplineCurve> Solution(
    const occ::handle<Geom2d_BSplineCurve>& BS,
    const double                            TolPoles = 0.000001,
    const double                            TolKnots = 0.000001);

  Standard_EXPORT static void Solutionbis(const occ::handle<Geom_BSplineCurve>& BS,
                                          double&                               Knotmin,
                                          double&                               Knotmax,
                                          const double                          TolPoles = 0.000001,
                                          const double TolKnots = 0.000001);
};
