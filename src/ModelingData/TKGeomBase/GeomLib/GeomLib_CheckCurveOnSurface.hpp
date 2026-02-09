#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Precision.hpp>
#include <Standard.hpp>

class Adaptor3d_CurveOnSurface;

class GeomLib_CheckCurveOnSurface
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT GeomLib_CheckCurveOnSurface();

  Standard_EXPORT GeomLib_CheckCurveOnSurface(const occ::handle<Adaptor3d_Curve>& theCurve,
                                              const double theTolRange = Precision::PConfusion());

  Standard_EXPORT void Init(const occ::handle<Adaptor3d_Curve>& theCurve,
                            const double theTolRange = Precision::PConfusion());

  Standard_EXPORT void Init();

  Standard_EXPORT void Perform(const occ::handle<Adaptor3d_CurveOnSurface>& theCurveOnSurface);

  void SetParallel(const bool theIsParallel) { myIsParallel = theIsParallel; }

  bool IsParallel() { return myIsParallel; }

  bool IsDone() const { return (myErrorStatus == 0); }

  int ErrorStatus() const { return myErrorStatus; }

  double MaxDistance() const { return myMaxDistance; }

  double MaxParameter() const { return myMaxParameter; }

private:
  occ::handle<Adaptor3d_Curve> myCurve;
  int                          myErrorStatus;
  double                       myMaxDistance;
  double                       myMaxParameter;
  double                       myTolRange;
  bool                         myIsParallel;
};
