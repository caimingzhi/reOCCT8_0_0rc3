#pragma once

#include <Standard.hpp>

#include <StepRepr_RepresentedDefinition.hpp>
#include <Standard_Transient.hpp>
class StepRepr_Representation;

//! Representation of STEP entity PropertyDefinitionRepresentation
class StepRepr_PropertyDefinitionRepresentation : public Standard_Transient
{

public:
  //! Empty constructor
  Standard_EXPORT StepRepr_PropertyDefinitionRepresentation();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const StepRepr_RepresentedDefinition&       aDefinition,
                            const occ::handle<StepRepr_Representation>& aUsedRepresentation);

  //! Returns field Definition
  Standard_EXPORT StepRepr_RepresentedDefinition Definition() const;

  //! Set field Definition
  Standard_EXPORT void SetDefinition(const StepRepr_RepresentedDefinition& Definition);

  //! Returns field UsedRepresentation
  Standard_EXPORT occ::handle<StepRepr_Representation> UsedRepresentation() const;

  //! Set field UsedRepresentation
  Standard_EXPORT void SetUsedRepresentation(
    const occ::handle<StepRepr_Representation>& UsedRepresentation);

  DEFINE_STANDARD_RTTIEXT(StepRepr_PropertyDefinitionRepresentation, Standard_Transient)

private:
  StepRepr_RepresentedDefinition       theDefinition;
  occ::handle<StepRepr_Representation> theUsedRepresentation;
};
