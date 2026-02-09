#pragma once

#include <Standard.hpp>
#include <Standard_Transient.hpp>

#include <TCollection_HAsciiString.hpp>

class StepRepr_RepresentationContextReference : public Standard_Transient
{
public:
  Standard_EXPORT StepRepr_RepresentationContextReference();

  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theContextIdentifier);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> ContextIdentifier() const;

  Standard_EXPORT void SetContextIdentifier(
    const occ::handle<TCollection_HAsciiString>& theContextIdentifier);

  DEFINE_STANDARD_RTTIEXT(StepRepr_RepresentationContextReference, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> myContextIdentifier;
};
