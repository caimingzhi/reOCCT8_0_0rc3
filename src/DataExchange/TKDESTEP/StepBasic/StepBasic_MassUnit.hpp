#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

class StepBasic_MassUnit : public StepBasic_NamedUnit
{

public:
  Standard_EXPORT StepBasic_MassUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_MassUnit, StepBasic_NamedUnit)
};
