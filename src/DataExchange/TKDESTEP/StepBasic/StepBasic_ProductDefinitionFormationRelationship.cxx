#include <StepBasic_ProductDefinitionFormation.hpp>
#include <StepBasic_ProductDefinitionFormationRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinitionFormationRelationship, Standard_Transient)

//=================================================================================================

StepBasic_ProductDefinitionFormationRelationship::
  StepBasic_ProductDefinitionFormationRelationship() = default;

//=================================================================================================

void StepBasic_ProductDefinitionFormationRelationship::Init(
  const occ::handle<TCollection_HAsciiString>&             aId,
  const occ::handle<TCollection_HAsciiString>&             aName,
  const occ::handle<TCollection_HAsciiString>&             aDescription,
  const occ::handle<StepBasic_ProductDefinitionFormation>& aRelatingProductDefinitionFormation,
  const occ::handle<StepBasic_ProductDefinitionFormation>& aRelatedProductDefinitionFormation)
{

  theId = aId;

  theName = aName;

  theDescription = aDescription;

  theRelatingProductDefinitionFormation = aRelatingProductDefinitionFormation;

  theRelatedProductDefinitionFormation = aRelatedProductDefinitionFormation;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinitionFormationRelationship::Id() const
{
  return theId;
}

//=================================================================================================

void StepBasic_ProductDefinitionFormationRelationship::SetId(
  const occ::handle<TCollection_HAsciiString>& aId)
{
  theId = aId;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinitionFormationRelationship::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_ProductDefinitionFormationRelationship::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinitionFormationRelationship::
  Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_ProductDefinitionFormationRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinitionFormation> StepBasic_ProductDefinitionFormationRelationship::
  RelatingProductDefinitionFormation() const
{
  return theRelatingProductDefinitionFormation;
}

//=================================================================================================

void StepBasic_ProductDefinitionFormationRelationship::SetRelatingProductDefinitionFormation(
  const occ::handle<StepBasic_ProductDefinitionFormation>& aRelatingProductDefinitionFormation)
{
  theRelatingProductDefinitionFormation = aRelatingProductDefinitionFormation;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinitionFormation> StepBasic_ProductDefinitionFormationRelationship::
  RelatedProductDefinitionFormation() const
{
  return theRelatedProductDefinitionFormation;
}

//=================================================================================================

void StepBasic_ProductDefinitionFormationRelationship::SetRelatedProductDefinitionFormation(
  const occ::handle<StepBasic_ProductDefinitionFormation>& aRelatedProductDefinitionFormation)
{
  theRelatedProductDefinitionFormation = aRelatedProductDefinitionFormation;
}
