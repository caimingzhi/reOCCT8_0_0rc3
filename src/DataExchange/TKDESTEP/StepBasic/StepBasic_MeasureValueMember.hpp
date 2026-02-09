#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <StepData_SelectReal.hpp>

class StepBasic_MeasureValueMember : public StepData_SelectReal
{

public:
  Standard_EXPORT StepBasic_MeasureValueMember();

  Standard_EXPORT bool HasName() const override;

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT bool SetName(const char* name) override;

  DEFINE_STANDARD_RTTIEXT(StepBasic_MeasureValueMember, StepData_SelectReal)

private:
  int thecase;
};
