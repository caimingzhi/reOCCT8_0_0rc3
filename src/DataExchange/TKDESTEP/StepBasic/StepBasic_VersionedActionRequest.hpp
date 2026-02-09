#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_VersionedActionRequest : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_VersionedActionRequest();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aId,
                            const occ::handle<TCollection_HAsciiString>& aVersion,
                            const occ::handle<TCollection_HAsciiString>& aPurpose,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& Id);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Version() const;

  Standard_EXPORT void SetVersion(const occ::handle<TCollection_HAsciiString>& Version);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Purpose() const;

  Standard_EXPORT void SetPurpose(const occ::handle<TCollection_HAsciiString>& Purpose);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_VersionedActionRequest, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theId;
  occ::handle<TCollection_HAsciiString> theVersion;
  occ::handle<TCollection_HAsciiString> thePurpose;
  occ::handle<TCollection_HAsciiString> theDescription;
  bool                                  defDescription;
};
