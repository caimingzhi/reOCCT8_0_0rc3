

#include <StepBasic_SecurityClassification.hpp>
#include <StepBasic_SecurityClassificationLevel.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_SecurityClassification, Standard_Transient)

StepBasic_SecurityClassification::StepBasic_SecurityClassification() = default;

void StepBasic_SecurityClassification::Init(
  const occ::handle<TCollection_HAsciiString>&              aName,
  const occ::handle<TCollection_HAsciiString>&              aPurpose,
  const occ::handle<StepBasic_SecurityClassificationLevel>& aSecurityLevel)
{

  name          = aName;
  purpose       = aPurpose;
  securityLevel = aSecurityLevel;
}

void StepBasic_SecurityClassification::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  name = aName;
}

occ::handle<TCollection_HAsciiString> StepBasic_SecurityClassification::Name() const
{
  return name;
}

void StepBasic_SecurityClassification::SetPurpose(
  const occ::handle<TCollection_HAsciiString>& aPurpose)
{
  purpose = aPurpose;
}

occ::handle<TCollection_HAsciiString> StepBasic_SecurityClassification::Purpose() const
{
  return purpose;
}

void StepBasic_SecurityClassification::SetSecurityLevel(
  const occ::handle<StepBasic_SecurityClassificationLevel>& aSecurityLevel)
{
  securityLevel = aSecurityLevel;
}

occ::handle<StepBasic_SecurityClassificationLevel> StepBasic_SecurityClassification::SecurityLevel()
  const
{
  return securityLevel;
}
