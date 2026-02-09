#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_BSplineCurve;

class GeomLib_Check2dBSplineCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_Check2dBSplineCurve(const occ::handle<Geom2d_BSplineCurve>& Curve,
                                              const double                            Tolerance,
                                              const double AngularTolerance);

  bool IsDone() const;

  Standard_EXPORT void NeedTangentFix(bool& FirstFlag, bool& SecondFlag) const;

  Standard_EXPORT void FixTangent(const bool FirstFlag, const bool LastFlag);

  Standard_EXPORT occ::handle<Geom2d_BSplineCurve> FixedTangent(const bool FirstFlag,
                                                                const bool LastFlag);

private:
  void FixTangentOnCurve(occ::handle<Geom2d_BSplineCurve>& theCurve,
                         const bool                        FirstFlag,
                         const bool                        LastFlag);

  occ::handle<Geom2d_BSplineCurve> myCurve;
  bool                             myDone;
  bool                             myFixFirstTangent;
  bool                             myFixLastTangent;
  double                           myAngularTolerance;
  double                           myTolerance;

  int myIndSecondPole;
  int myIndPrelastPole;
};

inline bool GeomLib_Check2dBSplineCurve::IsDone() const
{
  return myDone;
}
