#include <StepRepr_PropertyDefinitionRepresentation.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentedDefinition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_PropertyDefinitionRepresentation, Standard_Transient)

//=================================================================================================

StepRepr_PropertyDefinitionRepresentation::StepRepr_PropertyDefinitionRepresentation() = default;

//=================================================================================================

void StepRepr_PropertyDefinitionRepresentation::Init(
  const StepRepr_RepresentedDefinition&       aDefinition,
  const occ::handle<StepRepr_Representation>& aUsedRepresentation)
{

  theDefinition = aDefinition;

  theUsedRepresentation = aUsedRepresentation;
}

//=================================================================================================

StepRepr_RepresentedDefinition StepRepr_PropertyDefinitionRepresentation::Definition() const
{
  return theDefinition;
}

//=================================================================================================

void StepRepr_PropertyDefinitionRepresentation::SetDefinition(
  const StepRepr_RepresentedDefinition& aDefinition)
{
  theDefinition = aDefinition;
}

//=================================================================================================

occ::handle<StepRepr_Representation> StepRepr_PropertyDefinitionRepresentation::UsedRepresentation()
  const
{
  return theUsedRepresentation;
}

//=================================================================================================

void StepRepr_PropertyDefinitionRepresentation::SetUsedRepresentation(
  const occ::handle<StepRepr_Representation>& aUsedRepresentation)
{
  theUsedRepresentation = aUsedRepresentation;
}
