#include <StepRepr_DataEnvironment.hpp>
#include <StepRepr_MaterialPropertyRepresentation.hpp>
#include <StepRepr_Representation.hpp>
#include <StepRepr_RepresentedDefinition.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_MaterialPropertyRepresentation,
                           StepRepr_PropertyDefinitionRepresentation)

StepRepr_MaterialPropertyRepresentation::StepRepr_MaterialPropertyRepresentation() = default;

void StepRepr_MaterialPropertyRepresentation::Init(
  const StepRepr_RepresentedDefinition&        aPropertyDefinitionRepresentation_Definition,
  const occ::handle<StepRepr_Representation>&  aPropertyDefinitionRepresentation_UsedRepresentation,
  const occ::handle<StepRepr_DataEnvironment>& aDependentEnvironment)
{
  StepRepr_PropertyDefinitionRepresentation::Init(
    aPropertyDefinitionRepresentation_Definition,
    aPropertyDefinitionRepresentation_UsedRepresentation);

  theDependentEnvironment = aDependentEnvironment;
}

occ::handle<StepRepr_DataEnvironment> StepRepr_MaterialPropertyRepresentation::
  DependentEnvironment() const
{
  return theDependentEnvironment;
}

void StepRepr_MaterialPropertyRepresentation::SetDependentEnvironment(
  const occ::handle<StepRepr_DataEnvironment>& aDependentEnvironment)
{
  theDependentEnvironment = aDependentEnvironment;
}
