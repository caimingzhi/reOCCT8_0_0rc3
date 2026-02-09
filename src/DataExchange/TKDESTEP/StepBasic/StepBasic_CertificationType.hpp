#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_CertificationType : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_CertificationType();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  DEFINE_STANDARD_RTTIEXT(StepBasic_CertificationType, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theDescription;
};
