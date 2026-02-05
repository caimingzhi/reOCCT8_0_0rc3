#include <StepBasic_ProductDefinition.hpp>
#include <StepBasic_ProductDefinitionRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_ProductDefinitionRelationship, Standard_Transient)

//=================================================================================================

StepBasic_ProductDefinitionRelationship::StepBasic_ProductDefinitionRelationship()
{
  defDescription = false;
}

//=================================================================================================

void StepBasic_ProductDefinitionRelationship::Init(
  const occ::handle<TCollection_HAsciiString>&    aId,
  const occ::handle<TCollection_HAsciiString>&    aName,
  const bool                                      hasDescription,
  const occ::handle<TCollection_HAsciiString>&    aDescription,
  const occ::handle<StepBasic_ProductDefinition>& aRelatingProductDefinition,
  const occ::handle<StepBasic_ProductDefinition>& aRelatedProductDefinition)
{

  theId = aId;

  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theRelatingProductDefinition.SetValue(aRelatingProductDefinition);

  theRelatedProductDefinition.SetValue(aRelatedProductDefinition);
}

//=================================================================================================

void StepBasic_ProductDefinitionRelationship::Init(
  const occ::handle<TCollection_HAsciiString>&  aId,
  const occ::handle<TCollection_HAsciiString>&  aName,
  const bool                                    hasDescription,
  const occ::handle<TCollection_HAsciiString>&  aDescription,
  const StepBasic_ProductDefinitionOrReference& aRelatingProductDefinition,
  const StepBasic_ProductDefinitionOrReference& aRelatedProductDefinition)
{

  theId          = aId;
  theName        = aName;
  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();
  theRelatingProductDefinition = aRelatingProductDefinition;
  theRelatedProductDefinition  = aRelatedProductDefinition;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinitionRelationship::Id() const
{
  return theId;
}

//=================================================================================================

void StepBasic_ProductDefinitionRelationship::SetId(
  const occ::handle<TCollection_HAsciiString>& aId)
{
  theId = aId;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinitionRelationship::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_ProductDefinitionRelationship::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_ProductDefinitionRelationship::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_ProductDefinitionRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

//=================================================================================================

bool StepBasic_ProductDefinitionRelationship::HasDescription() const
{
  return defDescription;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinition> StepBasic_ProductDefinitionRelationship::
  RelatingProductDefinition() const
{
  return theRelatingProductDefinition.ProductDefinition();
}

//=================================================================================================

StepBasic_ProductDefinitionOrReference StepBasic_ProductDefinitionRelationship::
  RelatingProductDefinitionAP242() const
{
  return theRelatingProductDefinition;
}

//=================================================================================================

void StepBasic_ProductDefinitionRelationship::SetRelatingProductDefinition(
  const occ::handle<StepBasic_ProductDefinition>& aRelatingProductDefinition)
{
  theRelatingProductDefinition.SetValue(aRelatingProductDefinition);
}

//=================================================================================================

void StepBasic_ProductDefinitionRelationship::SetRelatingProductDefinition(
  const StepBasic_ProductDefinitionOrReference& aRelatingProductDefinition)
{
  theRelatingProductDefinition = aRelatingProductDefinition;
}

//=================================================================================================

occ::handle<StepBasic_ProductDefinition> StepBasic_ProductDefinitionRelationship::
  RelatedProductDefinition() const
{
  return theRelatedProductDefinition.ProductDefinition();
}

//=================================================================================================

StepBasic_ProductDefinitionOrReference StepBasic_ProductDefinitionRelationship::
  RelatedProductDefinitionAP242() const
{
  return theRelatedProductDefinition;
}

//=================================================================================================

void StepBasic_ProductDefinitionRelationship::SetRelatedProductDefinition(
  const occ::handle<StepBasic_ProductDefinition>& aRelatedProductDefinition)
{
  theRelatedProductDefinition.SetValue(aRelatedProductDefinition);
}

//=================================================================================================

void StepBasic_ProductDefinitionRelationship::SetRelatedProductDefinition(
  const StepBasic_ProductDefinitionOrReference& aRelatedProductDefinition)
{
  theRelatedProductDefinition = aRelatedProductDefinition;
}
