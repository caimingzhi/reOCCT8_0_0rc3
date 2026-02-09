#pragma once

#include <Standard.hpp>

#include <StepElement_CurveElementFreedom.hpp>
#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>

class StepElement_CurveElementEndReleasePacket : public Standard_Transient
{

public:
  Standard_EXPORT StepElement_CurveElementEndReleasePacket();

  Standard_EXPORT void Init(const StepElement_CurveElementFreedom& aReleaseFreedom,
                            const double                           aReleaseStiffness);

  Standard_EXPORT StepElement_CurveElementFreedom ReleaseFreedom() const;

  Standard_EXPORT void SetReleaseFreedom(const StepElement_CurveElementFreedom& ReleaseFreedom);

  Standard_EXPORT double ReleaseStiffness() const;

  Standard_EXPORT void SetReleaseStiffness(const double ReleaseStiffness);

  DEFINE_STANDARD_RTTIEXT(StepElement_CurveElementEndReleasePacket, Standard_Transient)

private:
  StepElement_CurveElementFreedom theReleaseFreedom;
  double                          theReleaseStiffness;
};
