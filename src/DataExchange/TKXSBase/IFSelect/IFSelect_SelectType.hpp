#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectAnyType.hpp>
class TCollection_AsciiString;

//! A SelectType keeps or rejects Entities of which the Type
//! is Kind of a given Cdl Type
class IFSelect_SelectType : public IFSelect_SelectAnyType
{

public:
  //! Creates a SelectType. Default is no filter
  Standard_EXPORT IFSelect_SelectType();

  //! Creates a SelectType for a given Type
  Standard_EXPORT IFSelect_SelectType(const occ::handle<Standard_Type>& atype);

  //! Sets a TYpe for filter
  Standard_EXPORT void SetType(const occ::handle<Standard_Type>& atype);

  //! Returns the Type to be matched for select : this is the type
  //! given at instantiation time
  Standard_EXPORT occ::handle<Standard_Type> TypeForMatch() const override;

  //! Returns a text defining the criterium.
  //! (should by gotten from Type of Entity used for instantiation)
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IFSelect_SelectType, IFSelect_SelectAnyType)

private:
  occ::handle<Standard_Type> thetype;
};
