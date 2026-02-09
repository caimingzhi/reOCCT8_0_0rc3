#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_SelectMember.hpp>
#include <Standard_Integer.hpp>

class StepData_SelectReal : public StepData_SelectMember
{

public:
  Standard_EXPORT StepData_SelectReal();

  Standard_EXPORT int Kind() const override;

  Standard_EXPORT double Real() const override;

  Standard_EXPORT void SetReal(const double val) override;

  DEFINE_STANDARD_RTTIEXT(StepData_SelectReal, StepData_SelectMember)

private:
  double theval;
};
