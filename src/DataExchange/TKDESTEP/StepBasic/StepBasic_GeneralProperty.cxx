#include <StepBasic_GeneralProperty.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_GeneralProperty, Standard_Transient)

StepBasic_GeneralProperty::StepBasic_GeneralProperty()
{
  defDescription = false;
}

void StepBasic_GeneralProperty::Init(const occ::handle<TCollection_HAsciiString>& aId,
                                     const occ::handle<TCollection_HAsciiString>& aName,
                                     const bool                                   hasDescription,
                                     const occ::handle<TCollection_HAsciiString>& aDescription)
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
}

occ::handle<TCollection_HAsciiString> StepBasic_GeneralProperty::Id() const
{
  return theId;
}

void StepBasic_GeneralProperty::SetId(const occ::handle<TCollection_HAsciiString>& aId)
{
  theId = aId;
}

occ::handle<TCollection_HAsciiString> StepBasic_GeneralProperty::Name() const
{
  return theName;
}

void StepBasic_GeneralProperty::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_GeneralProperty::Description() const
{
  return theDescription;
}

void StepBasic_GeneralProperty::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

bool StepBasic_GeneralProperty::HasDescription() const
{
  return defDescription;
}
