#pragma once

#include <Standard.hpp>
#include <Standard_Transient.hpp>

#include <StepRepr_RepresentationContextReference.hpp>

//! Representation of STEP entity RepresentationReference
class StepRepr_RepresentationReference : public Standard_Transient
{
public:
  //! default constructor
  Standard_EXPORT StepRepr_RepresentationReference();

  //! Initialize all fields (own and inherited)
  Standard_EXPORT void Init(
    const occ::handle<TCollection_HAsciiString>&                theId,
    const occ::handle<StepRepr_RepresentationContextReference>& theContextOfItems);

  //! Returns field Id
  Standard_EXPORT occ::handle<TCollection_HAsciiString> Id() const;
  //! Sets field Id
  Standard_EXPORT void SetId(const occ::handle<TCollection_HAsciiString>& theId);

  //! Returns field ContextOfItems
  Standard_EXPORT occ::handle<StepRepr_RepresentationContextReference> ContextOfItems() const;
  //! Sets field ContextOfItems
  Standard_EXPORT void SetContextOfItems(
    const occ::handle<StepRepr_RepresentationContextReference>& theContextOfItems);

  DEFINE_STANDARD_RTTIEXT(StepRepr_RepresentationReference, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>                myId;
  occ::handle<StepRepr_RepresentationContextReference> myContextOfItems;
};
