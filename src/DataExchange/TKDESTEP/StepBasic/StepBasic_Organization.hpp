#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_Organization : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_Organization();

  Standard_EXPORT void Init(const bool                                   hasAid,
                            const occ::handle<TCollection_HAsciiString>& aId,
                            const occ::handle<TCollection_HAsciiString>& aName,
                            const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& aId);

  Standard_EXPORT void UnSetId();

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT bool HasId() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& aName);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& aDescription);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  DEFINE_STANDARD_RTTIEXT(StepBasic_Organization, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> id;
  occ::handle<TCollection_HAsciiString> name;
  occ::handle<TCollection_HAsciiString> description;
  bool                                  hasId;
};
