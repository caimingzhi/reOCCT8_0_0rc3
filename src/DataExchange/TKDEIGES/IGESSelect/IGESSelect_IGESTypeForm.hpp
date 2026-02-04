#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_Signature.hpp>
#include <Standard_CString.hpp>
class Standard_Transient;
class Interface_InterfaceModel;

// Avoid possible conflict with SetForm macro defined by windows.h
#ifdef SetForm
  #undef SetForm
#endif

//! IGESTypeForm is a Signature specific to the IGES Norm :
//! it gives the signature under two possible forms :
//! - as "mmm nnn", with "mmm" as IGES Type Number, and "nnn"
//! as IGES From Number (even if = 0) [Default]
//! - as "mmm" alone, which gives only the IGES Type Number
class IGESSelect_IGESTypeForm : public IFSelect_Signature
{

public:
  //! Creates a Signature for IGES Type & Form Numbers
  //! If <withform> is False, for IGES Type Number only
  Standard_EXPORT IGESSelect_IGESTypeForm(const bool withform = true);

  //! Changes the mode for giving the Form Number
  Standard_EXPORT void SetForm(const bool withform);

  //! Returns the signature for IGES, "mmm nnn" or "mmm" according
  //! creation choice (Type & Form or Type only)
  Standard_EXPORT const char* Value(
    const occ::handle<Standard_Transient>&       ent,
    const occ::handle<Interface_InterfaceModel>& model) const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_IGESTypeForm, IFSelect_Signature)

private:
  bool theform;
};

