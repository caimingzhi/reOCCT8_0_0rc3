#include <StepRepr_DataEnvironment.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_DataEnvironment, Standard_Transient)

StepRepr_DataEnvironment::StepRepr_DataEnvironment() = default;

void StepRepr_DataEnvironment::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<TCollection_HAsciiString>& aDescription,
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_PropertyDefinitionRepresentation>>>&
    aElements)
{

  theName = aName;

  theDescription = aDescription;

  theElements = aElements;
}

occ::handle<TCollection_HAsciiString> StepRepr_DataEnvironment::Name() const
{
  return theName;
}

void StepRepr_DataEnvironment::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_DataEnvironment::Description() const
{
  return theDescription;
}

void StepRepr_DataEnvironment::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}

occ::handle<NCollection_HArray1<occ::handle<StepRepr_PropertyDefinitionRepresentation>>>
  StepRepr_DataEnvironment::Elements() const
{
  return theElements;
}

void StepRepr_DataEnvironment::SetElements(
  const occ::handle<NCollection_HArray1<occ::handle<StepRepr_PropertyDefinitionRepresentation>>>&
    aElements)
{
  theElements = aElements;
}
