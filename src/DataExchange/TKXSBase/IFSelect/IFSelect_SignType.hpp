#pragma once


#include <Standard.hpp>

#include <IFSelect_Signature.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

//! This Signature returns the cdl Type of an entity, under two
//! forms :
//! - complete dynamic type (package and class)
//! - class type, without package name
class IFSelect_SignType : public IFSelect_Signature
{

public:
  //! Returns a SignType
  //! <nopk> false (D) : complete dynamic type (name = Dynamic Type)
  //! <nopk> true : class type without pk (name = Class Type)
  Standard_EXPORT IFSelect_SignType(const bool nopk = false);

  //! Returns the Signature for a Transient object, as its Dynamic
  //! Type, with or without package name, according starting option
  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SignType, IFSelect_Signature)

private:
  bool thenopk;
};

