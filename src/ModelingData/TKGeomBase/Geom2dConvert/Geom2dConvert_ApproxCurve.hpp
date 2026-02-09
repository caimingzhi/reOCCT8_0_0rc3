#pragma once

#include <Adaptor2d_Curve2d.hpp>
#include <GeomAbs_Shape.hpp>
#include <Standard_OStream.hpp>

class Geom2d_BSplineCurve;
class Geom2d_Curve;

class Geom2dConvert_ApproxCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT Geom2dConvert_ApproxCurve(const occ::handle<Geom2d_Curve>& Curve,
                                            const double                     Tol2d,
                                            const GeomAbs_Shape              Order,
                                            const int                        MaxSegments,
                                            const int                        MaxDegree);

  Standard_EXPORT Geom2dConvert_ApproxCurve(const occ::handle<Adaptor2d_Curve2d>& Curve,
                                            const double                          Tol2d,
                                            const GeomAbs_Shape                   Order,
                                            const int                             MaxSegments,
                                            const int                             MaxDegree);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> Curve() const;

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT bool HasResult() const;

  Standard_EXPORT double MaxError() const;

  Standard_EXPORT void Dump(Standard_OStream& o) const;

private:
  Standard_EXPORT void Approximate(const occ::handle<Adaptor2d_Curve2d>& theCurve,
                                   const double                          theTol3d,
                                   const GeomAbs_Shape                   theOrder,
                                   const int                             theMaxSegments,
                                   const int                             theMaxDegree);

  bool                             myIsDone;
  bool                             myHasResult;
  occ::handle<Geom2d_BSplineCurve> myBSplCurve;
  double                           myMaxError;
};
