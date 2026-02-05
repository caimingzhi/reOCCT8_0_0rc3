#include <StepRepr_PropertyDefinition.hpp>
#include <StepRepr_PropertyDefinitionRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_PropertyDefinitionRelationship, Standard_Transient)

//=================================================================================================

StepRepr_PropertyDefinitionRelationship::StepRepr_PropertyDefinitionRelationship() = default;

//=================================================================================================

void StepRepr_PropertyDefinitionRelationship::Init(
  const occ::handle<TCollection_HAsciiString>&    aName,
  const occ::handle<TCollection_HAsciiString>&    aDescription,
  const occ::handle<StepRepr_PropertyDefinition>& aRelatingPropertyDefinition,
  const occ::handle<StepRepr_PropertyDefinition>& aRelatedPropertyDefinition)
{

  theName = aName;

  theDescription = aDescription;

  theRelatingPropertyDefinition = aRelatingPropertyDefinition;

  theRelatedPropertyDefinition = aRelatedPropertyDefinition;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepRepr_PropertyDefinitionRelationship::Name() const
{
  return theName;
}

//=================================================================================================

void StepRepr_PropertyDefinitionRelationship::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepRepr_PropertyDefinitionRelationship::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepRepr_PropertyDefinitionRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

occ::handle<StepRepr_PropertyDefinition> StepRepr_PropertyDefinitionRelationship::
  RelatingPropertyDefinition() const
{
  return theRelatingPropertyDefinition;
}

//=================================================================================================

void StepRepr_PropertyDefinitionRelationship::SetRelatingPropertyDefinition(
  const occ::handle<StepRepr_PropertyDefinition>& aRelatingPropertyDefinition)
{
  theRelatingPropertyDefinition = aRelatingPropertyDefinition;
}

//=================================================================================================

occ::handle<StepRepr_PropertyDefinition> StepRepr_PropertyDefinitionRelationship::
  RelatedPropertyDefinition() const
{
  return theRelatedPropertyDefinition;
}

//=================================================================================================

void StepRepr_PropertyDefinitionRelationship::SetRelatedPropertyDefinition(
  const occ::handle<StepRepr_PropertyDefinition>& aRelatedPropertyDefinition)
{
  theRelatedPropertyDefinition = aRelatedPropertyDefinition;
}
