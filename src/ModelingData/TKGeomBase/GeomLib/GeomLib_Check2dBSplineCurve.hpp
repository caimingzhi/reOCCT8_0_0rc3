#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

class Geom2d_BSplineCurve;

//! Checks for the end tangents : whether or not those
//! are reversed
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

  //! modifies the curve
  //! by fixing the first or the last tangencies
  //!
  //! if Index3D not in the Range [1,Nb3dSpaces]
  //! if the Approx is not Done
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
