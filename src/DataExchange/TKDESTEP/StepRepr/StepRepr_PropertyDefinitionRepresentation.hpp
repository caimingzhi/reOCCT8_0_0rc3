#pragma once

#include <Standard.hpp>

#include <StepRepr_RepresentedDefinition.hpp>
#include <Standard_Transient.hpp>
class StepRepr_Representation;

class StepRepr_PropertyDefinitionRepresentation : public Standard_Transient
{

public:
  Standard_EXPORT StepRepr_PropertyDefinitionRepresentation();

  Standard_EXPORT void Init(const StepRepr_RepresentedDefinition&       aDefinition,
                            const occ::handle<StepRepr_Representation>& aUsedRepresentation);

  Standard_EXPORT StepRepr_RepresentedDefinition Definition() const;

  Standard_EXPORT void SetDefinition(const StepRepr_RepresentedDefinition& Definition);

  Standard_EXPORT occ::handle<StepRepr_Representation> UsedRepresentation() const;

  Standard_EXPORT void SetUsedRepresentation(
    const occ::handle<StepRepr_Representation>& UsedRepresentation);

  DEFINE_STANDARD_RTTIEXT(StepRepr_PropertyDefinitionRepresentation, Standard_Transient)

private:
  StepRepr_RepresentedDefinition       theDefinition;
  occ::handle<StepRepr_Representation> theUsedRepresentation;
};
