#pragma once

#include <Standard.hpp>

#include <IFSelect_Signature.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

//! This Signature returns the Validity Status of an entity, as
//! deducted from data in the model : it can be
//! "OK" "Unknown" "Unloaded" "Syntactic Fail"(but loaded)
//! "Syntactic Warning" "Semantic Fail" "Semantic Warning"
class IFSelect_SignValidity : public IFSelect_Signature
{

public:
  //! Returns a SignValidity
  Standard_EXPORT IFSelect_SignValidity();

  //! Returns the Signature for a Transient object, as a validity
  //! deducted from data (reports) stored in the model.
  //! Class method, can be called by any one
  Standard_EXPORT static const char* CVal(const occ::handle<Standard_Transient>&       ent,
                                          const occ::handle<Interface_InterfaceModel>& model);

  //! Returns the Signature for a Transient object, as a validity
  //! deducted from data (reports) stored in the model
  //! Calls the class method CVal
  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SignValidity, IFSelect_Signature)
};
