#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <GeomAbs_Shape.hpp>

class Approx_Curve2d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Approx_Curve2d(const occ::handle<Adaptor2d_Curve2d>& C2D,
                                 const double                          First,
                                 const double                          Last,
                                 const double                          TolU,
                                 const double                          TolV,
                                 const GeomAbs_Shape                   Continuity,
                                 const int                             MaxDegree,
                                 const int                             MaxSegments);

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve() const;

  Standard_EXPORT double MaxError2dU() const;

  Standard_EXPORT double MaxError2dV() const;

private:
  occ::handle<Geom2d_BSplineCurve> myCurve;
  bool                             myIsDone;
  bool                             myHasResult;
  double                           myMaxError2dU;
  double                           myMaxError2dV;
};
