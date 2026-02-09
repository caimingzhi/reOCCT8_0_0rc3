#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Real.hpp>
#include <Standard_Boolean.hpp>
#include <HelixGeom_BuilderApproxCurve.hpp>

class HelixGeom_BuilderHelixGen : public HelixGeom_BuilderApproxCurve
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT void SetCurveParameters(const double aT1,
                                          const double aT2,
                                          const double aPitch,
                                          const double aRStart,
                                          const double aTaperAngle,
                                          const bool   bIsClockwise);

  Standard_EXPORT void CurveParameters(double& aT1,
                                       double& aT2,
                                       double& aPitch,
                                       double& aRStart,
                                       double& aTaperAngle,
                                       bool&   bIsClockwise) const;

protected:
  Standard_EXPORT HelixGeom_BuilderHelixGen();
  Standard_EXPORT ~HelixGeom_BuilderHelixGen() override;

  double myT1;
  double myT2;
  double myPitch;
  double myRStart;
  double myTaperAngle;
  bool   myIsClockWise;
};
