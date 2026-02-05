#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class StepBasic_Effectivity;

//! Representation of STEP entity EffectivityAssignment
class StepBasic_EffectivityAssignment : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepBasic_EffectivityAssignment();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<StepBasic_Effectivity>& aAssignedEffectivity);

  //! Returns field AssignedEffectivity
  Standard_EXPORT occ::handle<StepBasic_Effectivity> AssignedEffectivity() const;

  //! Set field AssignedEffectivity
  Standard_EXPORT void SetAssignedEffectivity(
    const occ::handle<StepBasic_Effectivity>& AssignedEffectivity);

  DEFINE_STANDARD_RTTIEXT(StepBasic_EffectivityAssignment, Standard_Transient)

private:
  occ::handle<StepBasic_Effectivity> theAssignedEffectivity;
};
