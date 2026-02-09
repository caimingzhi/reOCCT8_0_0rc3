#pragma once

#include <Adaptor3d_Curve.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_OStream.hpp>

class Geom_BSplineCurve;
class Geom_Curve;

class GeomConvert_ApproxCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomConvert_ApproxCurve(const occ::handle<Geom_Curve>& Curve,
                                          const double                   Tol3d,
                                          const GeomAbs_Shape            Order,
                                          const int                      MaxSegments,
                                          const int                      MaxDegree);

  Standard_EXPORT GeomConvert_ApproxCurve(const occ::handle<Adaptor3d_Curve>& Curve,
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
  Standard_EXPORT void Approximate(const occ::handle<Adaptor3d_Curve>& theCurve,
                                   const double                        theTol3d,
                                   const GeomAbs_Shape                 theOrder,
                                   const int                           theMaxSegments,
                                   const int                           theMaxDegree);

  bool                           myIsDone;
  bool                           myHasResult;
  occ::handle<Geom_BSplineCurve> myBSplCurve;
  double                         myMaxError;
};
