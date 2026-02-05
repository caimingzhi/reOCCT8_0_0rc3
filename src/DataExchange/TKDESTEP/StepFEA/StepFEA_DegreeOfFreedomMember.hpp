#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepData_SelectNamed.hpp>
#include <Standard_CString.hpp>

//! Representation of member for STEP SELECT type CurveElementFreedom
class StepFEA_DegreeOfFreedomMember : public StepData_SelectNamed
{

public:
  //! Empty constructor
  Standard_EXPORT StepFEA_DegreeOfFreedomMember();

  //! Returns True if has name
  Standard_EXPORT bool HasName() const override;

  //! Returns set name
  Standard_EXPORT const char* Name() const override;

  //! Set name
  Standard_EXPORT bool SetName(const char* name) override;

  //! Tells if the name of a SelectMember matches a given one;
  Standard_EXPORT bool Matches(const char* name) const override;

  DEFINE_STANDARD_RTTIEXT(StepFEA_DegreeOfFreedomMember, StepData_SelectNamed)

private:
  int mycase;
};
