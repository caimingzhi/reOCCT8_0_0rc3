#include <StepBasic_Certification.hpp>
#include <StepBasic_CertificationType.hpp>
#include <TCollection_HAsciiString.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepBasic_Certification, Standard_Transient)

//=================================================================================================

StepBasic_Certification::StepBasic_Certification() = default;

//=================================================================================================

void StepBasic_Certification::Init(const occ::handle<TCollection_HAsciiString>&    aName,
                                   const occ::handle<TCollection_HAsciiString>&    aPurpose,
                                   const occ::handle<StepBasic_CertificationType>& aKind)
{

  theName = aName;

  thePurpose = aPurpose;

  theKind = aKind;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_Certification::Name() const
{
  return theName;
}

//=================================================================================================

void StepBasic_Certification::SetName(const occ::handle<TCollection_HAsciiString>& aName)
{
  theName = aName;
}

//=================================================================================================

occ::handle<TCollection_HAsciiString> StepBasic_Certification::Purpose() const
{
  return thePurpose;
}

//=================================================================================================

void StepBasic_Certification::SetPurpose(const occ::handle<TCollection_HAsciiString>& aPurpose)
{
  thePurpose = aPurpose;
}

//=================================================================================================

occ::handle<StepBasic_CertificationType> StepBasic_Certification::Kind() const
{
  return theKind;
}

//=================================================================================================

void StepBasic_Certification::SetKind(const occ::handle<StepBasic_CertificationType>& aKind)
{
  theKind = aKind;
}
