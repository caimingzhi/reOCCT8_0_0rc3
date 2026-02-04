#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <StepBasic_NamedUnit.hpp>

//! Representation of STEP entity MassUnit
class StepBasic_MassUnit : public StepBasic_NamedUnit
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_MassUnit();

  DEFINE_STANDARD_RTTIEXT(StepBasic_MassUnit, StepBasic_NamedUnit)
};

