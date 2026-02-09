

#include <StepRepr_FunctionallyDefinedTransformation.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_FunctionallyDefinedTransformation, Standard_Transient)

StepRepr_FunctionallyDefinedTransformation::StepRepr_FunctionallyDefinedTransformation() = default;

void StepRepr_FunctionallyDefinedTransformation::Init(
  const occ::handle<TCollection_HAsciiString>& aName,
  const occ::handle<TCollection_HAsciiString>& aDescription)
{

  name        = aName;
  description = aDescription;
}

void StepRepr_FunctionallyDefinedTransformation::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepRepr_FunctionallyDefinedTransformation::Name() const
{
  return name;
}

void StepRepr_FunctionallyDefinedTransformation::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  description = aDescription;
}

occ::handle<TCollection_HAsciiString> StepRepr_FunctionallyDefinedTransformation::Description()
  const
{
  return description;
}
