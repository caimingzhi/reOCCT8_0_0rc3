#pragma once

#include <Standard.hpp>
#include <Standard_Transient.hpp>

#include <TCollection_HAsciiString.hpp>

//! Representation of STEP entity RepresentationContextReference
class StepRepr_RepresentationContextReference : public Standard_Transient
{
public:
  //! default constructor
  Standard_EXPORT StepRepr_RepresentationContextReference();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(const occ::handle<TCollection_HAsciiString>& theContextIdentifier);

  //! Returns field ContextIdentifier
  Standard_EXPORT occ::handle<TCollection_HAsciiString> ContextIdentifier() const;
  //! Sets field ContextIdentifier
  Standard_EXPORT void SetContextIdentifier(
    const occ::handle<TCollection_HAsciiString>& theContextIdentifier);

  DEFINE_STANDARD_RTTIEXT(StepRepr_RepresentationContextReference, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString> myContextIdentifier;
};
