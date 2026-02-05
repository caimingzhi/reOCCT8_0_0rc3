#pragma once

#include <Standard.hpp>

#include <StepElement_CurveElementFreedom.hpp>
#include <Standard_Real.hpp>
#include <Standard_Transient.hpp>

//! Representation of STEP entity CurveElementEndReleasePacket
class StepElement_CurveElementEndReleasePacket : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepElement_CurveElementEndReleasePacket();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepElement_CurveElementFreedom& aReleaseFreedom,
                            const double                           aReleaseStiffness);

  //! Returns field ReleaseFreedom
  Standard_EXPORT StepElement_CurveElementFreedom ReleaseFreedom() const;

  //! Set field ReleaseFreedom
  Standard_EXPORT void SetReleaseFreedom(const StepElement_CurveElementFreedom& ReleaseFreedom);

  //! Returns field ReleaseStiffness
  Standard_EXPORT double ReleaseStiffness() const;

  //! Set field ReleaseStiffness
  Standard_EXPORT void SetReleaseStiffness(const double ReleaseStiffness);

  DEFINE_STANDARD_RTTIEXT(StepElement_CurveElementEndReleasePacket, Standard_Transient)

private:
  StepElement_CurveElementFreedom theReleaseFreedom;
  double                          theReleaseStiffness;
};
