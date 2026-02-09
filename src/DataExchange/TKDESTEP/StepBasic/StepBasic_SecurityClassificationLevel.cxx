

#include <StepBasic_SecurityClassificationLevel.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SecurityClassificationLevel, Standard_Transient)

StepBasic_SecurityClassificationLevel::StepBasic_SecurityClassificationLevel() = default;

void StepBasic_SecurityClassificationLevel::Init(const occ::handle<TCollection_HAsciiString>& aName)
{

  name = aName;
}

void StepBasic_SecurityClassificationLevel::SetName(
  const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_SecurityClassificationLevel::Name() const
{
  return name;
}
