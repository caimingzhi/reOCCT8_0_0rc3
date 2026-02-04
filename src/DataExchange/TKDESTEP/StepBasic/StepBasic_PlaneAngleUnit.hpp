#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

class StepBasic_PlaneAngleUnit : public StepBasic_NamedUnit
{

public:
  //! Returns a PlaneAngleUnit
  Standard_EXPORT StepBasic_PlaneAngleUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_PlaneAngleUnit, StepBasic_NamedUnit)
};

