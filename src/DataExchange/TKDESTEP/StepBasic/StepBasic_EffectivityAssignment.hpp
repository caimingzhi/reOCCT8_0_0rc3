#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Effectivity;

class StepBasic_EffectivityAssignment : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_EffectivityAssignment();

  Standard_EXPORT void Init(const occ::handle<StepBasic_Effectivity>& aAssignedEffectivity);

  Standard_EXPORT occ::handle<StepBasic_Effectivity> AssignedEffectivity() const;

  Standard_EXPORT void SetAssignedEffectivity(
    const occ::handle<StepBasic_Effectivity>& AssignedEffectivity);

  DEFINE_STANDARD_RTTIEXT(StepBasic_EffectivityAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Effectivity> theAssignedEffectivity;
};
