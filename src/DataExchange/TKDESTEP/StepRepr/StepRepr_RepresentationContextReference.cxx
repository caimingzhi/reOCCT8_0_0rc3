

#include <StepRepr_RepresentationContextReference.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_RepresentationContextReference, Standard_Transient)

StepRepr_RepresentationContextReference::StepRepr_RepresentationContextReference() = default;

void StepRepr_RepresentationContextReference::Init(
  const occ::handle<TCollection_HAsciiString>& theContextIdentifier)
{

  myContextIdentifier = theContextIdentifier;
}

occ::handle<TCollection_HAsciiString> StepRepr_RepresentationContextReference::ContextIdentifier()
  const
{
  return myContextIdentifier;
}

void StepRepr_RepresentationContextReference::SetContextIdentifier(
  const occ::handle<TCollection_HAsciiString>& theContextIdentifier)
{
  myContextIdentifier = theContextIdentifier;
}
