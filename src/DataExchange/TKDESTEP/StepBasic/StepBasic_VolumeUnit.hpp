#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

class StepBasic_VolumeUnit : public StepBasic_NamedUnit
{

public:
  Standard_EXPORT StepBasic_VolumeUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_VolumeUnit, StepBasic_NamedUnit)
};

