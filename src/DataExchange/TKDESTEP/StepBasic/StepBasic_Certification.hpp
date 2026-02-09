#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_CertificationType;

class StepBasic_Certification : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_Certification();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>&    aName,
                            const occ::handle<TCollection_HAsciiString>&    aPurpose,
                            const occ::handle<StepBasic_CertificationType>& aKind);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Purpose() const;

  Standard_EXPORT void SetPurpose(const occ::handle<TCollection_HAsciiString>& Purpose);

  Standard_EXPORT occ::handle<StepBasic_CertificationType> Kind() const;

  Standard_EXPORT void SetKind(const occ::handle<StepBasic_CertificationType>& Kind);

  DEFINE_STANDARD_RTTIEXT(StepBasic_Certification, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>    theName;
  occ::handle<TCollection_HAsciiString>    thePurpose;
  occ::handle<StepBasic_CertificationType> theKind;
};
