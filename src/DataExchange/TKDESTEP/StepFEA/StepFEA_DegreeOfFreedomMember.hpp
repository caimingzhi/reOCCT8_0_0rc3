#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepData_SelectNamed.hpp>
#include <Standard_CString.hpp>

class StepFEA_DegreeOfFreedomMember : public StepData_SelectNamed
{

public:
  Standard_EXPORT StepFEA_DegreeOfFreedomMember();

  Standard_EXPORT bool HasName() const override;

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT bool SetName(const char* name) override;

  Standard_EXPORT bool Matches(const char* name) const override;

  DEFINE_STANDARD_RTTIEXT(StepFEA_DegreeOfFreedomMember, StepData_SelectNamed)

private:
  int mycase;
};
