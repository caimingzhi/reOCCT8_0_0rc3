

#include <StepShape_TypeQualifier.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepShape_TypeQualifier, Standard_Transient)

StepShape_TypeQualifier::StepShape_TypeQualifier() = default;

void StepShape_TypeQualifier::Init(const occ::handle<TCollection_HAsciiString>& name)
{
  theName = name;
}

occ::handle<TCollection_HAsciiString> StepShape_TypeQualifier::Name() const
{
  return theName;
}

void StepShape_TypeQualifier::SetName(const occ::handle<TCollection_HAsciiString>& name)
{
  theName = name;
}
