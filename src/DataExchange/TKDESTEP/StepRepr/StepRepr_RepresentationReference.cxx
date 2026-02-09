

#include <StepRepr_RepresentationReference.hpp>

IMPLEMENT_STANDARD_RTTIEXT(StepRepr_RepresentationReference, Standard_Transient)

StepRepr_RepresentationReference::StepRepr_RepresentationReference() = default;

void StepRepr_RepresentationReference::Init(
  const occ::handle<TCollection_HAsciiString>&                theId,
  const occ::handle<StepRepr_RepresentationContextReference>& theContextOfItems)
{

  myId = theId;

  myContextOfItems = theContextOfItems;
}

occ::handle<TCollection_HAsciiString> StepRepr_RepresentationReference::Id() const
{
  return myId;
}

void StepRepr_RepresentationReference::SetId(const occ::handle<TCollection_HAsciiString>& theId)
{
  myId = theId;
}

occ::handle<StepRepr_RepresentationContextReference> StepRepr_RepresentationReference::
  ContextOfItems() const
{
  return myContextOfItems;
}

void StepRepr_RepresentationReference::SetContextOfItems(
  const occ::handle<StepRepr_RepresentationContextReference>& theContextOfItems)
{
  myContextOfItems = theContextOfItems;
}
