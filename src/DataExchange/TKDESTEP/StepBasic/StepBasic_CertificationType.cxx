#include <StepBasic_CertificationType.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_CertificationType, Standard_Transient)

//=================================================================================================

StepBasic_CertificationType::StepBasic_CertificationType() = default;

//=================================================================================================

void StepBasic_CertificationType::Init(const occ::handle<TCollection_HAsciiString>& aDescription)
{

  theDescription = aDescription;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_CertificationType::Description() const
{
  return theDescription;
}

//=================================================================================================

void StepBasic_CertificationType::SetDescription(
  const occ::handle<TCollection_HAsciiString>& aDescription)
{
  theDescription = aDescription;
}
