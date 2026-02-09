#pragma once

#include <Standard.hpp>

#include <Standard_Integer.hpp>
#include <StepData_SelectArrReal.hpp>
#include <Standard_Boolean.hpp>
#include <Standard_CString.hpp>

class StepFEA_SymmetricTensor43dMember : public StepData_SelectArrReal
{

public:
  Standard_EXPORT StepFEA_SymmetricTensor43dMember();

  Standard_EXPORT bool HasName() const override;

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT bool SetName(const char* name) override;

  Standard_EXPORT bool Matches(const char* name) const override;

  DEFINE_STANDARD_RTTIEXT(StepFEA_SymmetricTensor43dMember, StepData_SelectArrReal)

private:
  int mycase;
};
