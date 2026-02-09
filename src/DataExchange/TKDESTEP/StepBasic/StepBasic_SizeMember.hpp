#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepData_SelectReal.hpp>

class StepBasic_SizeMember : public StepData_SelectReal
{

public:
  Standard_EXPORT StepBasic_SizeMember();

  Standard_EXPORT bool HasName() const override;

  Standard_EXPORT const char* Name() const override;

  Standard_EXPORT bool SetName(const char* name) override;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SizeMember, StepData_SelectReal)
};
