

#include <StepBasic_GeneralProperty.hpp>
#include <StepBasic_GeneralPropertyRelationship.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_GeneralPropertyRelationship, Standard_Transient)

StepBasic_GeneralPropertyRelationship::StepBasic_GeneralPropertyRelationship() = default;

void StepBasic_GeneralPropertyRelationship::Init(
  const occ::handle<TCollection_HAsciiString>&  aName,
  const bool                                    hasDescription,
  const occ::handle<TCollection_HAsciiString>&  aDescription,
  const occ::handle<StepBasic_GeneralProperty>& aRelatingGeneralProperty,
  const occ::handle<StepBasic_GeneralProperty>& aRelatedGeneralProperty)
{
  theName = aName;

  defDescription = hasDescription;
  if (defDescription)
  {
    theDescription = aDescription;
  }
  else
    theDescription.Nullify();

  theRelatingGeneralProperty = aRelatingGeneralProperty;

  theRelatedGeneralProperty = aRelatedGeneralProperty;
}

occ::handle<TCollection_HAsciiString> StepBasic_GeneralPropertyRelationship::Name() const
{
  return theName;
}

void StepBasic_GeneralPropertyRelationship::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

bool StepBasic_GeneralPropertyRelationship::HasDescription() const
{
  return defDescription;
}

occ::handle<TCollection_HAsciiString> StepBasic_GeneralPropertyRelationship::Description() const
{
  return theDescription;
}

void StepBasic_GeneralPropertyRelationship::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  defDescription = true;
  if (aDescription.IsNull())
  {
    defDescription = false;
  }
  theDescription = aDescription;
}

occ::handle<StepBasic_GeneralProperty> StepBasic_GeneralPropertyRelationship::
  RelatingGeneralProperty() const
{
  return theRelatingGeneralProperty;
}

void StepBasic_GeneralPropertyRelationship::SetRelatingGeneralProperty(
  const occ::handle<StepBasic_GeneralProperty>& aRelatingGeneralProperty)
{
  theRelatingGeneralProperty = aRelatingGeneralProperty;
}

occ::handle<StepBasic_GeneralProperty> StepBasic_GeneralPropertyRelationship::
  RelatedGeneralProperty() const
{
  return theRelatedGeneralProperty;
}

void StepBasic_GeneralPropertyRelationship::SetRelatedGeneralProperty(
  const occ::handle<StepBasic_GeneralProperty>& aRelatedGeneralProperty)
{
  theRelatedGeneralProperty = aRelatedGeneralProperty;
}
