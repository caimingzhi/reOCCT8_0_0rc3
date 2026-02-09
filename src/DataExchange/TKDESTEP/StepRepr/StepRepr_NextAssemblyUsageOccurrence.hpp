#pragma once

#include <Standard.hpp>

#include <StepRepr_AssemblyComponentUsage.hpp>

class StepRepr_NextAssemblyUsageOccurrence : public StepRepr_AssemblyComponentUsage
{

public:
  Standard_EXPORT StepRepr_NextAssemblyUsageOccurrence();

  DEFINE_STANDARD_RTTIEXT(StepRepr_NextAssemblyUsageOccurrence, StepRepr_AssemblyComponentUsage)
};
