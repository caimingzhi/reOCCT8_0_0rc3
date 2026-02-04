#pragma once


#include <Standard.hpp>

#include <IFSelect_Signature.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

//! This Signature returns the Category of an entity, as recorded
//! in the model
class IFSelect_SignCategory : public IFSelect_Signature
{

public:
  //! Returns a SignCategory
  Standard_EXPORT IFSelect_SignCategory();

  //! Returns the Signature for a Transient object, as its Category
  //! recorded in the model
  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SignCategory, IFSelect_Signature)
};

