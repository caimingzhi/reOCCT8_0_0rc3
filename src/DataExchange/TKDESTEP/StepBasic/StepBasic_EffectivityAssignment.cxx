#include <Standard_Type.hpp>
#include <StepBasic_Effectivity.hpp>
#include <StepBasic_EffectivityAssignment.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_EffectivityAssignment, Standard_Transient)

//=================================================================================================

StepBasic_EffectivityAssignment::StepBasic_EffectivityAssignment() = default;

//=================================================================================================

void StepBasic_EffectivityAssignment::Init(
  const occ::handle<StepBasic_Effectivity>& aAssignedEffectivity)
{

  theAssignedEffectivity = aAssignedEffectivity;
}

//=================================================================================================

occ::handle<StepBasic_Effectivity> StepBasic_EffectivityAssignment::AssignedEffectivity() const
{
  return theAssignedEffectivity;
}

//=================================================================================================

void StepBasic_EffectivityAssignment::SetAssignedEffectivity(
  const occ::handle<StepBasic_Effectivity>& aAssignedEffectivity)
{
  theAssignedEffectivity = aAssignedEffectivity;
}
