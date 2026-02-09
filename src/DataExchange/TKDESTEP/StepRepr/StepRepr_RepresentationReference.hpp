#pragma once

#include <Standard.hpp>
#include <Standard_Transient.hpp>

#include <StepRepr_RepresentationContextReference.hpp>

class StepRepr_RepresentationReference : public Standard_Transient
{
public:
  Standard_EXPORT StepRepr_RepresentationReference();

  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                theId,
    const occ::handle<StepRepr_RepresentationContextReference>& theContextOfItems);

  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;

  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& theId);

  Standard_EXPORT occ::handle<StepRepr_RepresentationContextReference> ContextOfItems() const;

  Standard_EXPORT void SetContextOfItems(
    const occ::handle<StepRepr_RepresentationContextReference>& theContextOfItems);

  DEFINE_STANDARD_RTTIEXT(StepRepr_RepresentationReference, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                myId;
  occ::handle<StepRepr_RepresentationContextReference> myContextOfItems;
};
