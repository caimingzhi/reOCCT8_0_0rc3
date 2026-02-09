#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <Geom_BSplineCurve.hpp>

class Approx_Curve3d
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Approx_Curve3d(const occ::handle<Adaptor3d_Curve>& Curve,
                                 const double                        Tol3d,
                                 const GeomAbs_Shape                 Order,
                                 const int                           MaxSegments,
                                 const int                           MaxDegree);

  Standard_EXPORT occ::handle<Geom_BSplineCurve> Curve() const;

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT double MaxError() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  bool                           myIsDone;
  bool                           myHasResult;
  occ::handle<Geom_BSplineCurve> myBSplCurve;
  double                         myMaxError;
};
