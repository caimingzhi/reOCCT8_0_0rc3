

#include <StepBasic_GeneralPropertyAssociation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_GeneralPropertyAssociation, Standard_Transient)

StepBasic_GeneralPropertyAssociation::StepBasic_GeneralPropertyAssociation() = default;

void StepBasic_GeneralPropertyAssociation::Init(
  const occ::handle<TCollection_HAsciiString>&    aName,
  const occ::handle<TCollection_HAsciiString>&    aDescription,
  const occ::handle<StepBasic_GeneralProperty>&   aGeneralProperty,
  const occ::handle<StepRepr_PropertyDefinition>& aPropertyDefinition)
{
  theName = aName;

  theDescription = aDescription;

  theGeneralProperty = aGeneralProperty;

  thePropertyDefinition = aPropertyDefinition;
}

occ::handle<TCollection_HAsciiString> StepBasic_GeneralPropertyAssociation::Name() const
{
  return theName;
}

void StepBasic_GeneralPropertyAssociation::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_GeneralPropertyAssociation::Description() const
{
  return theDescription;
}

void StepBasic_GeneralPropertyAssociation::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

occ::handle<StepBasic_GeneralProperty> StepBasic_GeneralPropertyAssociation::GeneralProperty() const
{
  return theGeneralProperty;
}

void StepBasic_GeneralPropertyAssociation::SetGeneralProperty(
  const occ::handle<StepBasic_GeneralProperty>& aGeneralProperty)
{
  theGeneralProperty = aGeneralProperty;
}

occ::handle<StepRepr_PropertyDefinition> StepBasic_GeneralPropertyAssociation::PropertyDefinition()
  const
{
  return thePropertyDefinition;
}

void StepBasic_GeneralPropertyAssociation::SetPropertyDefinition(
  const occ::handle<StepRepr_PropertyDefinition>& aPropertyDefinition)
{
  thePropertyDefinition = aPropertyDefinition;
}
