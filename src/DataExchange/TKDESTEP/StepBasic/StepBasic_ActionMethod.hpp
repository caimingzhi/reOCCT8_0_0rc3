#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Boolean.hpp>
#include <Standard_Transient.hpp>
class TCollection_HAsciiString;

class StepBasic_ActionMethod : public Standard_Transient
{

public:
  Standard_EXPORT StepBasic_ActionMethod();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& aName,
                            const bool                                   hasDescription,
                            const occ::handle<TCollection_HAsciiString>& aDescription,
                            const occ::handle<TCollection_HAsciiString>& aConsequence,
                            const occ::handle<TCollection_HAsciiString>& aPurpose);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Name() const;

  Standard_EXPORT void SetName(const occ::handle<TCollection_HAsciiString>& Name);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Description() const;

  Standard_EXPORT void SetDescription(const occ::handle<TCollection_HAsciiString>& Description);

  Standard_EXPORT bool HasDescription() const;

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Consequence() const;

  Standard_EXPORT void SetConsequence(const occ::handle<TCollection_HAsciiString>& Consequence);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Purpose() const;

  Standard_EXPORT void SetPurpose(const occ::handle<TCollection_HAsciiString>& Purpose);

  DEFINE_STANDARD_RTTIEXT(StepBasic_ActionMethod, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> theName;
  occ::handle<TCollection_HAsciiString> theDescription;
  occ::handle<TCollection_HAsciiString> theConsequence;
  occ::handle<TCollection_HAsciiString> thePurpose;
  bool                                  defDescription;
};
