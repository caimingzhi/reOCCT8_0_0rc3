#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
class TCollection_HAsciiString;
class StepBasic_SecurityClassificationLevel;

class StepBasic_SecurityClassification : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_SecurityClassification();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&              aName,
    const occ::handle<TCollection_HAsciiString>&              aPurpose,
    const occ::handle<StepBasic_SecurityClassificationLevel>& aSecurityLevel);

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetPurpose(const occ::handle<TCollection_HAsciiString>& aPurpose);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Purpose() const;

  Standard_EXPORT void SetSecurityLevel(
    const occ::handle<StepBasic_SecurityClassificationLevel>& aSecurityLevel);

  Standard_EXPORT occ::handle<StepBasic_SecurityClassificationLevel> SecurityLevel() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_SecurityClassification, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>              name;
  occ::handle<TCollection_HAsciiString>              purpose;
  occ::handle<StepBasic_SecurityClassificationLevel> securityLevel;
};
