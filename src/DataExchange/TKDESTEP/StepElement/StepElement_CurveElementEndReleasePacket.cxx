#include <StepElement_CurveElementEndReleasePacket.hpp>
#include <StepElement_CurveElementFreedom.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepElement_CurveElementEndReleasePacket, Standard_Transient)

StepElement_CurveElementEndReleasePacket::StepElement_CurveElementEndReleasePacket() = default;

void StepElement_CurveElementEndReleasePacket::Init(
  const StepElement_CurveElementFreedom& aReleaseFreedom,
  const double                           aReleaseStiffness)
{

  theReleaseFreedom = aReleaseFreedom;

  theReleaseStiffness = aReleaseStiffness;
}

StepElement_CurveElementFreedom StepElement_CurveElementEndReleasePacket::ReleaseFreedom() const
{
  return theReleaseFreedom;
}

void StepElement_CurveElementEndReleasePacket::SetReleaseFreedom(
  const StepElement_CurveElementFreedom& aReleaseFreedom)
{
  theReleaseFreedom = aReleaseFreedom;
}

double StepElement_CurveElementEndReleasePacket::ReleaseStiffness() const
{
  return theReleaseStiffness;
}

void StepElement_CurveElementEndReleasePacket::SetReleaseStiffness(const double aReleaseStiffness)
{
  theReleaseStiffness = aReleaseStiffness;
}
