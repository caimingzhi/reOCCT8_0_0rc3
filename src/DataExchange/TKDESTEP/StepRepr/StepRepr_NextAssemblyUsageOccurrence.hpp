#pragma once

#include <Standard.hpp>

#include <StepRepr_AssemblyComponentUsage.hpp>

//! Representation of STEP entity NextAssemblyUsageOccurrence
class StepRepr_NextAssemblyUsageOccurrence : public StepRepr_AssemblyComponentUsage
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_NextAssemblyUsageOccurrence();

  DEFINE_STANDARD_RTTIEXT(StepRepr_NextAssemblyUsageOccurrence, StepRepr_AssemblyComponentUsage)
};
